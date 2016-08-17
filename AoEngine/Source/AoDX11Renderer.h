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

protected:
	virtual void CreateDevice() override;
	virtual void CreateDepthStencilBuffer() override;
	virtual void CreateRenderTarget() override;

private:
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;

	ID3D11RenderTargetView* RenderTargetView = nullptr;

	ID3D11DepthStencilView* DepthStencilView = nullptr;

	D3D11_TEXTURE2D_DESC BackBufferDesc;

};