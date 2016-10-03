#include "AoMaterialTextureProperty.h"

AoMaterialTextureProperty::AoMaterialTextureProperty( AoTexture2D* Data, const string& Name )
	: Data( Data ), AoMaterialProperty( Name )
{
}

AoTexture2D* AoMaterialTextureProperty::GetData( ) const
{
	return Data;
}

void AoMaterialTextureProperty::SetData( AoTexture2D* Data )
{
	this->Data = Data;
}

void AoMaterialTextureProperty::ApplyToGlobalVariable( AoShader* Shader ) const
{
	Shader->SetGlobalTextureByName( Name, Data );
}
