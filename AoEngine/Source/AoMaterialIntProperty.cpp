#include "AoMaterialIntProperty.h"

AoMaterialIntProperty::AoMaterialIntProperty( int Data, const string& PropertyName )
	: Data( Data ), AoMaterialProperty( PropertyName )
{
}

int AoMaterialIntProperty::GetData( ) const
{
	return Data;
}

void AoMaterialIntProperty::SetData( int Data )
{
	this->Data = Data;
}

void AoMaterialIntProperty::ApplyToGlobalVariable( AoShader* Shader ) const
{
	Shader->SetGlobalIntByName( Name, Data );
}
