#pragma once
#include "AoComponent.h"
#include "AoMaterial.h"

class AoRenderer;
class AoRenderComponent : public AoComponent
{
	friend AoRenderer;

public:
	AoRenderComponent();
	~AoRenderComponent();

	virtual void Render( AoRenderer* Renderer ) = 0;

	void SetMaterial( AoMaterial* Material );
	AoMaterial* GetMaterial() const;

	void SetActiveTechnique( const string& TechniqueName );

	/** Is Visible 메소드는 컴포넌트가 Actor에 Attach 되어 있는지 여부를 확인함. */
	bool IsVisible() const;
	void SetIsVisible( bool bIsVisible );

	bool IsRegistered() const;

	virtual void OnAttach( ) override;
	virtual void OnDetach( ) override;

protected:
	AoRenderer& Renderer;
	AoMaterial* Material;

	ID3DX11EffectTechnique* ActiveTechnique;

	bool bIsVisible;

private:
	bool bIsRegistered;

};