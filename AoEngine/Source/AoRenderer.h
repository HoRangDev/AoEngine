#pragma once
#include "WindowsInc.h"
#include <vector>

class AoWindow;
class AoRenderComponent;
class AoRenderer
{
public:
	using RenderComponentVector = std::vector<AoRenderComponent*>;
	using RenderComponentVectorItr = RenderComponentVector::iterator;
	using RenderComponentVectorConstItr = RenderComponentVector::const_iterator;

public:
	AoRenderer( AoWindow& Window );
	virtual ~AoRenderer();

	virtual void BeginFrame() = 0;
	virtual void Render() final;
	virtual void EndFrame() = 0;

	virtual void RegisterComponent( AoRenderComponent* RenderComponent ) final;
	virtual void UnRegisterComponent( AoRenderComponent* RenderComponent ) final;

protected:
	virtual void CreateDevice() = 0;
	virtual void CreateRenderTarget() = 0;

protected:
	AoWindow& Window;
	RenderComponentVector Components;

};