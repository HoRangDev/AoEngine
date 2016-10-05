#include "AoMaterialData.h"

AoMaterialData::AoMaterialData( ) 
	: Ambient( AoVector4::One ), Diffuse( AoVector4::One ), Specular( AoVector4::One ), Emissive( AoVector4::Zero )
{
}

AoMaterialData::AoMaterialData( const AoVector4& Ambient, const AoVector4& Diffuse, const AoVector4& Specular, const AoVector4& Emissive )
	: Ambient( Ambient ), Diffuse( Diffuse ), Specular( Specular ), Emissive( Emissive )
{
}

AoVector4 AoMaterialData::GetAmbient( ) const
{
	return Ambient;
}

void AoMaterialData::SetAmbient( const AoVector4& Ambient )
{
	this->Ambient = Ambient;
}

AoVector4 AoMaterialData::GetDiffuse( ) const
{
	return Diffuse;
}

void AoMaterialData::SetDiffuse( const AoVector4& Diffuse )
{
	this->Diffuse = Diffuse;
}

AoVector4 AoMaterialData::GetSpecular( ) const
{
	return Specular;
}

void AoMaterialData::SetSpecular( const AoVector4& Specular )
{
	this->Specular = Specular;
}

AoVector4 AoMaterialData::GetEmissive( ) const
{
	return Emissive;
}

void AoMaterialData::SetEmissive( const AoVector4& Emissive )
{
	this->Emissive = Emissive;
}
