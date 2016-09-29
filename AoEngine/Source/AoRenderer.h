#pragma once
#include "WindowsInc.h"
#include "AoViewport.h"
#include <list>

class AoWindow;
class AoRenderComponent;
class AoRenderer
{
public:
	using RenderComponentList = std::list<AoRenderComponent*>;
	using RenderComponentListItr = RenderComponentList::iterator;
	using RenderComponentListConstItr = RenderComponentList::const_iterator;

public:
	AoRenderer( AoWindow& Window );
	virtual ~AoRenderer();

	virtual void BeginFrame();
	virtual void Render();
	virtual void EndFrame();

	virtual void RegisterComponent(AoRenderComponent* RenderComponent);
	virtual void UnRegisterComponent(AoRenderComponent* RenderComponent);

	virtual float GetBackBufferWidth() const;
	virtual float GetBackBufferHeight() const;

	void SetViewport( const AoViewport& Viewport );

	virtual void ResizeBackBuffer();

	ID3D11Device* GetDevice( ) const;
	ID3D11DeviceContext* GetDeviceContext( ) const;

protected:
	virtual void CreateDevice();
	virtual void CreateDepthStencilBuffer();
	virtual void CreateRenderTarget();
	virtual void Release();

private:
	AoWindow& Window;
	AoViewport Viewport;
	RenderComponentList Components;

	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;

	ID3D11RenderTargetView* RenderTargetView = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;

	D3D11_TEXTURE2D_DESC BackBufferDesc;

	bool bIsStandByMode = false;

};