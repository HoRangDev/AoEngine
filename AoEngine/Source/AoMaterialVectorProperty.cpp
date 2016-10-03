#include "AoMaterialVectorProperty.h"

AoMaterialVectorProperty::AoMaterialVectorProperty( const AoVector4& Data, const string& Name )
	: Data( Data ), AoMaterialProperty( Name )
{
}

AoVector4 AoMaterialVectorProperty::GetData( ) const
{
	return Data;
}

void AoMaterialVectorProperty::SetData( const AoVector4& Data )
{
	this->Data = Data;
}

void AoMaterialVectorProperty::ApplyToGlobalVariable( AoShader* Shader ) const
{
	Shader->SetGlobalVectorByName( Name, Data );
}
