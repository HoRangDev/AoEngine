#pragma once
#include "AoRenderer.h"

class AoWindow;
class AoDX11Renderer : public AoRenderer
{
public:
	AoDX11Renderer( AoWindow& Window );
	virtual ~AoDX11Renderer();

	virtual void BeginFrame() override;
	virtual void EndFrame() override;

	virtual float GetBackBufferWidth() const override;
	virtual float GetBackBufferHeight() const override;

	virtual void ResizeBackBuffer() override;

	/** Set Resolution Test */
	//void Test()
	//{
	//	// Test
	//	DXGI_MODE_DESC Desc;
	//	Desc.Width = 1280;
	//	Desc.Height = 720;
	//	Desc.RefreshRate.Numerator = 60;
	//	Desc.RefreshRate.Denominator = 1;
	//	Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//	Desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//	Desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//	SwapChain->ResizeTarget( &Desc );
	//}

protected:
	virtual void CreateDevice() override;
	virtual void CreateDepthStencilBuffer() override;
	virtual void CreateRenderTarget() override;
	virtual void ReleaseRenderer() override;

private:
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;

	ID3D11RenderTargetView* RenderTargetView = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;

	D3D11_TEXTURE2D_DESC BackBufferDesc;

	bool bIsStandByMode = false;

};