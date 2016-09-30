#include "AoVector2.h"
#include "AoMath.h"

const AoVector2 AoVector2::Zero = AoVector2( 0.0f, 0.0f );
const AoVector2 AoVector2::One = AoVector2( 1.0f, 1.0f );

AoVector2::AoVector2( float X, float Y ) :
	X( X ),
	Y( Y )
	{

	}

	AoVector2& AoVector2::operator=( const AoVector2& Operand )
{
	X = Operand.X;
	Y = Operand.Y;
	return *this;
}

AoVector2 AoVector2::operator+( float Operand )
{
	return AoVector2(
		X + Operand,
		Y + Operand );
}

AoVector2 AoVector2::operator+( const AoVector2& Operand )
{
	return AoVector2(
		X + Operand.X,
		Y + Operand.Y );
}

AoVector2& AoVector2::operator+=( float Operand )
{
	X += Operand;
	Y += Operand;
	return *this;
}

AoVector2& AoVector2::operator+=( const AoVector2& Operand )
{
	X += Operand.X;
	Y += Operand.Y;
	return *this;
}

AoVector2 AoVector2::operator-( float Operand )
{
	return AoVector2(
		X - Operand,
		Y - Operand );
}

AoVector2 AoVector2::operator-( const AoVector2 & Operand )
{
	return AoVector2(
		X - Operand.X,
		Y - Operand.Y );
}

AoVector2& AoVector2::operator-=( float Operand )
{
	X -= Operand;
	Y -= Operand;
	return *this;
}

AoVector2& AoVector2::operator-=( const AoVector2& Operand )
{
	X -= Operand.X;
	Y -= Operand.Y;
	return *this;
}

AoVector2 AoVector2::operator*( float Operand )
{
	return AoVector2(
		X * Operand,
		Y * Operand );
}

AoVector2 AoVector2::operator*( const AoVector2& Operand )
{
	return AoVector2(
		X * Operand.X,
		Y * Operand.Y );
}

AoVector2& AoVector2::operator*=( float Operand )
{
	X *= Operand;
	Y *= Operand;
	return *this;
}

AoVector2& AoVector2::operator*=( const AoVector2& Operand )
{
	X *= Operand.X;
	Y *= Operand.Y;
	return *this;
}

AoVector2 AoVector2::operator/( float Operand )
{
	float InvOperand = 1.0f / Operand;
	return AoVector2(
		X * InvOperand,
		Y * InvOperand );
}

AoVector2 AoVector2::operator/( const AoVector2& Operand )
{
	return AoVector2(
		X / Operand.X,
		Y / Operand.Y );
}

AoVector2& AoVector2::operator/=( float Operand )
{
	float InvOperand = 1.0f / Operand;
	X *= InvOperand;
	Y *= InvOperand;
	return *this;
}

AoVector2& AoVector2::operator/=( const AoVector2& Operand )
{
	X /= Operand.X;
	Y /= Operand.Y;
	return *this;
}

float AoVector2::operator|( const AoVector2& Operand )
{
	return ( X * Operand.X + Y * Operand.Y );
}

void AoVector2::SetX( float X )
{
	this->X = X;
}

float AoVector2::GetX( ) const
{
	return X;
}

void AoVector2::SetY( float Y )
{
	this->Y = Y;
}

float AoVector2::GetY( ) const
{
	return Y;
}

float AoVector2::Size( ) const
{
	return sqrtf( ( X * X + Y * Y ) );
}

float AoVector2::SquaredSize( ) const
{
	return ( X * X + Y * Y );
}

void AoVector2::Normalize( )
{
	float InvSize = 1.0f / Size( );
	X *= InvSize;
	Y *= InvSize;
}

AoVector2 AoVector2::GetNormal( ) const
{
	float InvSize = 1.0f / Size( );
	return AoVector2( X * InvSize, Y * InvSize );
}

bool AoVector2::IsUnit( ) const
{
	return ( Size( ) == 1.0f );
}

bool AoVector2::IsOne( ) const
{
	return ( X == 1.0f && Y == 1.0f );
}

bool AoVector2::IsZero( ) const
{
	return ( X == 0.0f && Y == 0.0f );
}