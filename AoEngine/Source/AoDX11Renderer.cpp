#include "AoDX11Renderer.h"
#include "AoWindow.h"

AoDX11Renderer::AoDX11Renderer( AoWindow& Window ) :
	AoRenderer( Window )
{
	CreateDevice();
	CreateRenderTarget();
}

AoDX11Renderer::~AoDX11Renderer()
{
	RenderTargetView->Release();
	SwapChain->Release();
	DeviceContext->Release();
	Device->Release();
}

void AoDX11Renderer::BeginFrame()
{
	float ClearColor[ 4 ] = { 0.0f, 0.0f, 0.0f, 1.0f };
	DeviceContext->ClearRenderTargetView( RenderTargetView, ClearColor );
}

void AoDX11Renderer::EndFrame()
{
	SwapChain->Present( 1, 0 );
}

void AoDX11Renderer::CreateDevice()
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0 };
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = Window.GetHandle();
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.Windowed = true;

	auto Result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION, &SwapChainDesc,
		&SwapChain, &Device, nullptr, &DeviceContext );

	if ( Result != S_OK )
	{
		MessageBox( nullptr, TEXT( "Problem Initialize DirectX 11!" ), TEXT( "Error!" ), MB_OK );
		exit( 0 );
	}
}

void AoDX11Renderer::CreateRenderTarget()
{
	ID3D11Texture2D* BackBuffer = nullptr;
	SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<void**>( &BackBuffer ) );
	Device->CreateRenderTargetView( BackBuffer, nullptr, &RenderTargetView );
	BackBuffer->Release();
}