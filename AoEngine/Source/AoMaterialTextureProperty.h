#pragma once
#include "AoMaterialProperty.h"

class AoTexture2D;
class AoMaterialTextureProperty : public AoMaterialProperty
{
public:
	AoMaterialTextureProperty( AoTexture2D* Data, const string& Name );
	AoTexture2D* GetData( ) const;
	void SetData( AoTexture2D* Data );

	virtual void ApplyToGlobalVariable( AoShader* Shader ) const;

private:
	AoTexture2D* Data;

};