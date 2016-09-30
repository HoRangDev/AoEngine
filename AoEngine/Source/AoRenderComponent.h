#pragma once
#include "AoComponent.h"
#include "AoMaterial.h"

class AoRenderer;
class AoShader;
class AoRenderComponent : public AoComponent
{
public:
	AoRenderComponent();
	~AoRenderComponent();

	virtual void Render() = 0;

	void SetMaterial( AoMaterial Material );
	AoMaterial GetMaterial() const;

	/** Is Visible 메소드는 컴포넌트가 Actor에 Attach 되어 있는지 여부를 확인함. */
	bool IsVisible() const;
	void SetIsVisible( bool bIsVisible );

	bool IsRegistered() const;

protected:
	AoRenderer* Renderer;
	AoShader*	Shader;
	AoMaterial  Material;
	bool bIsVisible;

private:
	bool bIsRegistered;

	friend AoRenderer;

};