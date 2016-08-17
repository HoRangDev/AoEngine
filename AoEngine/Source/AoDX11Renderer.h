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

protected:
	virtual void CreateDevice() override;
	virtual void CreateRenderTarget() override;

private:
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;

	ID3D11RenderTargetView* RenderTargetView = nullptr;

};