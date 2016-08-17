#include "AoDX11Renderer.h"
#include "AoWindow.h"
#include "AoViewport.h"

AoDX11Renderer::AoDX11Renderer( AoWindow& Window ) :
	AoRenderer( Window )
{
	CreateDevice();
	CreateDepthStencilBuffer();
	CreateRenderTarget();
	SetViewport( AoViewport( GetBackBufferWidth(), GetBackBufferHeight() ) );
}

AoDX11Renderer::~AoDX11Renderer()
{
	ReleaseRenderer();
}

void AoDX11Renderer::BeginFrame()
{
	DeviceContext->OMSetRenderTargets( 1, &RenderTargetView, DepthStencilView );

	auto D3DViewport = CD3D11_VIEWPORT( Viewport.TopLeftX, Viewport.TopLeftY, Viewport.Width, Viewport.Height );
	DeviceContext->RSSetViewports( 1, &D3DViewport );

	float ClearColor[ 4 ] = { 0.0f, 0.0f, 0.0f, 1.0f };
	DeviceContext->ClearRenderTargetView( RenderTargetView, ClearColor );
	DeviceContext->ClearDepthStencilView( DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0 );
}

void AoDX11Renderer::EndFrame()
{
	if( bIsStandByMode )
	{
		bIsStandByMode = (SwapChain->Present( 0, DXGI_PRESENT_TEST ) == DXGI_STATUS_OCCLUDED);
	}
	else
	{
		bIsStandByMode = ( SwapChain->Present( 0, 0 ) == DXGI_STATUS_OCCLUDED );
	}
}

float AoDX11Renderer::GetBackBufferWidth() const
{
	return static_cast<float>(BackBufferDesc.Width);
}

float AoDX11Renderer::GetBackBufferHeight() const
{
	return static_cast<float>(BackBufferDesc.Height);
}

void AoDX11Renderer::ResizeBackBuffer()
{
	DeviceContext->OMSetRenderTargets( 0, nullptr, nullptr );
	SwapChain->ResizeBuffers( 1, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0 );
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

void AoDX11Renderer::CreateDepthStencilBuffer()
{
	D3D11_TEXTURE2D_DESC DepthStencilDesc = { 0 };
	DepthStencilDesc.Width = Window.GetWidth();
	DepthStencilDesc.Height = Window.GetHeight();
	DepthStencilDesc.MipLevels = 1;
	DepthStencilDesc.ArraySize = 1;
	DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilDesc.SampleDesc.Count = 1;
	DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* DepthStencilBuffer = nullptr;
	
	Device->CreateTexture2D( &DepthStencilDesc, nullptr, &DepthStencilBuffer );
	Device->CreateDepthStencilView( DepthStencilBuffer, nullptr, &DepthStencilView );
	DepthStencilBuffer->Release();
}

void AoDX11Renderer::CreateRenderTarget()
{
	ID3D11Texture2D* BackBuffer = nullptr;
	SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<void**>( &BackBuffer ) );
	Device->CreateRenderTargetView( BackBuffer, nullptr, &RenderTargetView );
	BackBuffer->GetDesc( &BackBufferDesc );
	BackBuffer->Release();
}

void AoDX11Renderer::ReleaseRenderer()
{
	SwapChain->SetFullscreenState( false, nullptr );
	DeviceContext->ClearState();
	RenderTargetView->Release();
	DepthStencilView->Release();
	SwapChain->Release();
	DeviceContext->Release();
	Device->Release();
}
