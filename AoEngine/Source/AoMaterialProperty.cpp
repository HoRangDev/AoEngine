#include "AoMaterialProperty.h"

AoMaterialProperty::AoMaterialProperty( const string& Name )
	: Name( Name )
{
}

string AoMaterialProperty::GetName( ) const
{
	return Name;
}

void AoMaterialProperty::SetName( const string& Name )
{
	this->Name = Name;
}

void AoMaterialProperty::SetDirty( bool bIsDirty )
{
	this->bIsDirty = bIsDirty;
}

bool AoMaterialProperty::IsDirty( ) const
{
	return bIsDirty;
}
