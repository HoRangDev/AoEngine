#pragma once
#include "AoMaterialProperty.h"
#include "AoVector4.h"

class AoMaterialVectorProperty : public AoMaterialProperty
{
public:
	AoMaterialVectorProperty( const AoVector4& Data, const string& Name );
	AoVector4 GetData( ) const;
	void SetData( const AoVector4& Data );

	virtual void ApplyToGlobalVariable( AoShader* Shader ) const override;

private:
	AoVector4 Data;

};