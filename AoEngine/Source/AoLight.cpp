#include "AoLight.h"

AoLight::AoLight( )
	: Ambient( AoVector4::One ), Diffuse( AoVector4::One ),
	Specular( AoVector::One ), SpecularExponent( 1.0f ),
	Position( AoVector::Zero ), Range( 0.0f ),
	Direction( AoVector::Zero ), SpotExponent( 1.0f ),
	ConstantAttenuation( 0.0f ), LinearAttenuation( 0.0f ), QuadraticAttenuation( 1.0f ),
	LightType( ELightType::Directional )
{

}

AoVector4 AoLight::GetAmbient( ) const
{
	return Ambient;
}

void AoLight::SetAmbient( const AoVector4& Ambient )
{
	this->Ambient = Ambient;
}

AoVector4 AoLight::GetDiffuse( ) const
{
	return Diffuse;
}

void AoLight::SetDiffuse( const AoVector4& Diffuse )
{
	this->Diffuse = Diffuse;
}

AoVector AoLight::GetSpecular( ) const
{
	return Specular;
}

void AoLight::SetSpecular( const AoVector& Specular )
{
	this->Specular = Specular;
}

float AoLight::GetSpecularExponent( ) const
{
	return SpecularExponent;
}

void AoLight::SetSpecularExponent( float Exponent )
{
	this->SpecularExponent = Exponent;
}

AoVector AoLight::GetPosition( ) const
{
	return Position;
}

void AoLight::SetPosition( const AoVector& Position )
{
	this->Position = Position;
}

float AoLight::GetRange( ) const
{
	return Range;
}

void AoLight::SetRange( float Range )
{
	this->Range = Range;
}

AoVector AoLight::GetDirection( ) const
{
	return Direction;
}

void AoLight::SetDirection( const AoVector& Direction )
{
	this->Direction = Direction;
}

float AoLight::GetSpotExponent( ) const
{
	return SpotExponent;
}

void AoLight::SetSpotExponent( float Exponent )
{
	this->SpotExponent = Exponent;
}

float AoLight::GetConstantAttenuation( ) const
{
	return ConstantAttenuation;
}

void AoLight::SetConstantAttenuation( float Value )
{
	this->ConstantAttenuation = Value;
}

float AoLight::GetLinearAttenuation( ) const
{
	return LinearAttenuation;
}

void AoLight::SetLinearAttenuation( float Value )
{
	this->LinearAttenuation = Value;
}

float AoLight::GetQuadraticAttenuation( ) const
{
	return QuadraticAttenuation;
}

void AoLight::SetQuadraticAttenuation( float Value )
{
	this->QuadraticAttenuation = Value;
}

ELightType AoLight::GetLightType( ) const
{
	return LightType;
}

void AoLight::SetLightType( ELightType Type )
{
	this->LightType = Type;
}