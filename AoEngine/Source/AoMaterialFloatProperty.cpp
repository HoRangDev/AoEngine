#include "AoMaterialFloatProperty.h"

AoMaterialFloatProperty::AoMaterialFloatProperty( float Data, const string& Name )
	: Data( Data ), AoMaterialProperty( Name )
{
}

float AoMaterialFloatProperty::GetData( ) const
{
	return Data;
}

void AoMaterialFloatProperty::SetData( float Data )
{
	this->Data = Data;
}

void AoMaterialFloatProperty::ApplyToGlobalVariable( AoShader* Shader ) const
{
	Shader->SetGlobalFloatByName( Name, Data );
}
