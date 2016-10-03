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
