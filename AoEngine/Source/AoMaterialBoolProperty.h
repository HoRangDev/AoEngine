#pragma once
#include "AoMaterialProperty.h"

class AoMaterialBoolProperty : public AoMaterialProperty
{
public:
	AoMaterialBoolProperty( bool Data, const string& Name );
	bool GetData( ) const;
	void SetData( bool Data );

	virtual void ApplyToGlobalVariable( AoShader* Shader ) const  override;

private:
	bool Data;

};