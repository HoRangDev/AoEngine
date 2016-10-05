#pragma once
#include "AoType.h"
#include "WindowsInc.h"
#include "DirectXInc.h"
#include "AoViewport.h"
#include <list>

enum class EPrimitiveTopology
{
	Point,
	Line,
	Triangle,
};

class AoWindow;
class AoRenderComponent;
class AoCameraComponent;
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

	AoCameraComponent* GetMainCamera( ) const;
	void SetMainCamera( AoCameraComponent* Camera );

	void BindVertexBuffer( ID3D11Buffer* const Buffer, uint32 VertexSize );
	void BindIndexBuffer( ID3D11Buffer* const Buffer );

	void BindInputLayout( ID3D11InputLayout* const Layout );

	void SetPrimitiveTopology( EPrimitiveTopology Type );

	void ApplyPass( ID3DX11EffectPass* const Pass );

	void DrawIndexed( uint32 IndexCount, uint32 StartIndexLocation = 0, uint32 BaseVertexLocation = 0 );

protected:
	virtual void CreateDevice();
	virtual void CreateDepthStencilBuffer();
	virtual void CreateRenderTarget();
	virtual void Release();

private:
	AoWindow& Window;
	AoViewport Viewport;
	AoCameraComponent* MainCamera;
	RenderComponentList Components;

	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;

	ID3D11RenderTargetView* RenderTargetView = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;

	D3D11_TEXTURE2D_DESC BackBufferDesc;

	bool bIsStandByMode = false;

};