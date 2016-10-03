#pragma once
#include "AoMaterialProperty.h"

class AoMaterialIntProperty : public AoMaterialProperty
{
public:
	AoMaterialIntProperty( int Data, const string& PropertyName );
	int GetData( ) const;
	void SetData( int Data );

	virtual void ApplyToGlobalVariable( AoShader* Shader ) const  override;

private:
	int Data;

};