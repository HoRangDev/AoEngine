#pragma once
#include "AoMaterialProperty.h"

class AoMaterialFloatProperty : public AoMaterialProperty
{
public:
	AoMaterialFloatProperty( float Data, const string& Name );
	float GetData( ) const;
	void  SetData( float Data );

	virtual void ApplyToGlobalVariable( AoShader* Shader ) const override;

private:
	float Data;

};