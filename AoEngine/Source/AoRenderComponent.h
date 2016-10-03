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

	virtual void Render() = 0;

	void SetMaterial( AoMaterial* Material );
	AoMaterial* GetMaterial() const;

	/** Is Visible �޼ҵ�� ������Ʈ�� Actor�� Attach �Ǿ� �ִ��� ���θ� Ȯ����. */
	bool IsVisible() const;
	void SetIsVisible( bool bIsVisible );

	bool IsRegistered() const;

protected:
	AoRenderer& Renderer;
	AoMaterial*  Material;
	bool bIsVisible;

private:
	bool bIsRegistered;

};