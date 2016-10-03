#include "AoMaterialBoolProperty.h"

AoMaterialBoolProperty::AoMaterialBoolProperty( bool Data, const string& Name )
	: Data( Data ), AoMaterialProperty( Name )
{
}

bool AoMaterialBoolProperty::GetData( ) const
{
	return Data;
}

void AoMaterialBoolProperty::SetData( bool Data )
{
	this->Data = Data;
}

void AoMaterialBoolProperty::ApplyToGlobalVariable( AoShader* Shader ) const
{
	Shader->SetGlobalBoolByName( Name, Data );
}
