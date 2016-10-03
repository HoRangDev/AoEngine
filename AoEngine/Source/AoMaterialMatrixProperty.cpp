#include "AoMaterialMatrixProperty.h"

AoMaterialMatrixProperty::AoMaterialMatrixProperty( const AoMatrix4x4& Data, const string& Name )
	: Data( Data ), AoMaterialProperty( Name )
{
}

AoMatrix4x4 AoMaterialMatrixProperty::GetData( ) const
{
	return Data;
}

void AoMaterialMatrixProperty::SetData( const AoMatrix4x4& Data )
{
	this->Data = Data;
}

void AoMaterialMatrixProperty::ApplyToGlobalVariable( AoShader* Shader ) const
{
	Shader->SetGlobalMatrixByName( Name, Data );
}
