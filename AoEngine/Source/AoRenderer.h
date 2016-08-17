#pragma once
#include "WindowsInc.h"
#include "AoViewport.h"
#include <list>

class AoWindow;
class AoRenderComponent;
struct AoViewport;
class AoRenderer
{
public:
	using RenderComponentList = std::list<AoRenderComponent*>;
	using RenderComponentListItr = RenderComponentList::iterator;
	using RenderComponentListConstItr = RenderComponentList::const_iterator;

public:
	AoRenderer( AoWindow& Window );
	virtual ~AoRenderer();

	virtual void BeginFrame() = 0;
	virtual void Render() final;
	virtual void EndFrame() = 0;

	virtual void RegisterComponent( AoRenderComponent* RenderComponent ) final;
	virtual void UnRegisterComponent( AoRenderComponent* RenderComponent ) final;

	virtual float GetBackBufferWidth() const;
	virtual float GetBackBufferHeight() const;

	void SetViewport( const AoViewport& Viewport );

	virtual void ResizeBackBuffer() = 0;

protected:
	virtual void CreateDevice() = 0;
	virtual void CreateDepthStencilBuffer() = 0;
	virtual void CreateRenderTarget() = 0;
	virtual void ReleaseRenderer() = 0;

protected:
	AoWindow& Window;
	AoViewport Viewport;
	RenderComponentList Components;

};