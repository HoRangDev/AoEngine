#pragma once
#include "AoComponent.h"

class AoRenderer;
class AoMaterial;
class AoRenderComponent : public AoComponent
{
public:
	AoRenderComponent();
	~AoRenderComponent();

	virtual void Render() = 0;

	void SetMaterial( AoMaterial* Material );
	AoMaterial* GetMaterial() const;

	virtual void SetActive( bool bIsActive ) override;

	/** Is Visible 메소드는 컴포넌트가 Actor에 Attach 되어 있는지 여부를 확인함. */
	bool IsVisible() const;
	void SetIsVisible( bool bIsVisible );

	bool IsRegistered() const;

protected:
	AoRenderer* Renderer;
	AoMaterial* Material;
	bool bIsVisible;

private:
	bool bIsRegistered;

};