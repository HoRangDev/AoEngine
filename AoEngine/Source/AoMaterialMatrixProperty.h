#pragma once
#include "AoMaterialProperty.h"
#include "AoMatrix4x4.h"

class AoMaterialMatrixProperty : public AoMaterialProperty
{
public:
	AoMaterialMatrixProperty( const AoMatrix4x4& Data, const string& Name );
	AoMatrix4x4 GetData( ) const;
	void SetData( const AoMatrix4x4& Data );

	virtual void ApplyToGlobalVariable( AoShader* Shader ) const override;

private:
	AoMatrix4x4 Data;

};