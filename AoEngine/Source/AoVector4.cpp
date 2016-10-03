#include "AoVector4.h"
#include "AoMatrix4x4.h"
#include "AoMath.h"

const AoVector4 AoVector4::Zero = AoVector4( 0.0f, 0.0f, 0.0f, 0.0f );
const AoVector4 AoVector4::One = AoVector4( 1.0f, 1.0f, 1.0f, 1.0f );

AoVector4::AoVector4( float X, float Y, float Z, float W ) :
	X( X ),
	Y( Y ),
	Z( Z ),
	W( W )
{

}

AoVector4 & AoVector4::operator=( const AoVector4 & Operand )
{
	X = Operand.X;
	Y = Operand.Y;
	Z = Operand.Z;
	W = Operand.W;
	return *this;
}

AoVector4 AoVector4::operator+( float Operand )
{
	return AoVector4(
		X + Operand,
		Y + Operand,
		Z + Operand,
		W + Operand );
}

AoVector4 AoVector4::operator+( const AoVector4 & Operand )
{
	return AoVector4(
		X + Operand.X,
		Y + Operand.Y,
		Z + Operand.Z,
		W + Operand.W );
}

AoVector4 & AoVector4::operator+=( float Operand )
{
	X += Operand;
	Y += Operand;
	Z += Operand;
	W += Operand;
	return *this;
}

AoVector4 & AoVector4::operator+=( const AoVector4 & Operand )
{
	X += Operand.X;
	Y += Operand.Y;
	Z += Operand.Z;
	W += Operand.W;
	return *this;
}

AoVector4 AoVector4::operator-( float Operand )
{
	return AoVector4(
		X - Operand,
		Y - Operand,
		Z - Operand,
		W - Operand );
}

AoVector4 AoVector4::operator-( const AoVector4 & Operand )
{
	return AoVector4(
		X - Operand.X,
		Y - Operand.Y,
		Z - Operand.Z,
		W - Operand.W );
}

AoVector4 & AoVector4::operator-=( float Operand )
{
	X -= Operand;
	Y -= Operand;
	Z -= Operand;
	W -= Operand;
	return *this;
}

AoVector4 & AoVector4::operator-=( const AoVector4 & Operand )
{
	X -= Operand.X;
	Y -= Operand.Y;
	Z -= Operand.Z;
	W -= Operand.W;
	return *this;
}

AoVector4 AoVector4::operator*( float Operand )
{
	return AoVector4(
		X * Operand,
		Y * Operand,
		Z * Operand,
		W * Operand );
}

AoVector4 AoVector4::operator*( const AoVector4 & Operand )
{
	return AoVector4(
		X * Operand.X,
		Y * Operand.Y,
		Z * Operand.Z,
		W * Operand.W );
}

AoVector4 AoVector4::operator*( const AoMatrix4x4& Operand )
{
	AoVector4 Vector;
	Vector.X = ( Operand.M[ 0 ][ 0 ] * X ) + ( Operand.M[ 0 ][ 1 ] * Y ) + ( Operand.M[ 0 ][ 2 ] * Z ) + ( Operand.M[ 0 ][ 3 ] * W );
	Vector.Y = ( Operand.M[ 1 ][ 0 ] * X ) + ( Operand.M[ 1 ][ 1 ] * Y ) + ( Operand.M[ 1 ][ 2 ] * Z ) + ( Operand.M[ 1 ][ 3 ] * W );
	Vector.Z = ( Operand.M[ 2 ][ 0 ] * X ) + ( Operand.M[ 2 ][ 1 ] * Y ) + ( Operand.M[ 2 ][ 2 ] * Z ) + ( Operand.M[ 2 ][ 3 ] * W );
	Vector.W = ( Operand.M[ 3 ][ 0 ] * X ) + ( Operand.M[ 3 ][ 1 ] * Y ) + ( Operand.M[ 3 ][ 2 ] * Z ) + ( Operand.M[ 3 ][ 3 ] * W );
	return Vector;
}

AoVector4 & AoVector4::operator*=( float Operand )
{
	X *= Operand;
	Y *= Operand;
	Z *= Operand;
	W *= Operand;
	return *this;
}

AoVector4 & AoVector4::operator*=( const AoVector4 & Operand )
{
	X *= Operand.X;
	Y *= Operand.Y;
	Z *= Operand.Z;
	W *= Operand.W;
	return *this;
}

AoVector4 AoVector4::operator/( float Operand )
{
	return AoVector4(
		X / Operand,
		Y / Operand,
		Z / Operand,
		W / Operand );
}

AoVector4 AoVector4::operator/( const AoVector4 & Operand )
{
	return AoVector4(
		X / Operand.X,
		Y / Operand.Y,
		Z / Operand.Z,
		W / Operand.W );
}

AoVector4 & AoVector4::operator/=( float Operand )
{
	float InvOperand = 1.0f / Operand;
	X *= InvOperand;
	Y *= InvOperand;
	Z *= InvOperand;
	W *= InvOperand;
	return *this;
}

AoVector4 & AoVector4::operator/=( const AoVector4 & Operand )
{
	X /= Operand.X;
	Y /= Operand.Y;
	Z /= Operand.Z;
	W /= Operand.W;
	return *this;
}

float AoVector4::operator|( const AoVector4 & Operand )
{
	return ( X * Operand.X + Y * Operand.Y + Z * Operand.Z + W * Operand.W );
}

AoVector4 AoVector4::operator^( const AoVector4 & Operand )
{
	return AoVector4(
		Y * Operand.Z - Z * Operand.Y,
		Z * Operand.X - X * Operand.Z,
		X * Operand.Y - Y * Operand.X,
		0.0f
	);
}

void AoVector4::SetX( float X )
{
	this->X = X;
}

float AoVector4::GetX( ) const
{
	return X;
}

void AoVector4::SetY( float Y )
{
	this->Y = Y;
}

float AoVector4::GetY( ) const
{
	return Y;
}

void AoVector4::SetZ( float Z )
{
	this->Z = Z;
}

float AoVector4::GetZ( ) const
{
	return Z;
}

void AoVector4::SetW( float W )
{
	this->W = W;
}

float AoVector4::GetW( ) const
{
	return W;
}

float AoVector4::Size3( ) const
{
	return sqrt( X*X + Y*Y + Z*Z );
}

float AoVector4::SquaredSize3( ) const
{
	return ( X*X + Y*Y + Z*Z );
}

float AoVector4::Size4( ) const
{
	return sqrt( X*X + Y*Y + Z*Z + W*W );
}

float AoVector4::SquaredSize4( ) const
{
	return ( X*X + Y*Y + Z*Z + W*W );
}

void AoVector4::Normalize3( )
{
	float InvSize3 = 1.0f / Size3( );
	X *= InvSize3;
	Y *= InvSize3;
	Z *= InvSize3;
	W = 0.0f;
}

AoVector4 AoVector4::GetNormal3( ) const
{
	float InvSize3 = 1.0f / Size3( );
	return AoVector4( X * InvSize3, Y * InvSize3, Z * InvSize3 );
}

bool AoVector4::IsUnit( ) const
{
	return ( Size3( ) == 1.0f );
}

bool AoVector4::IsOne( ) const
{
	return ( X == 1.0f ) && ( Y == 1.0f ) && ( Z == 1.0f ) && ( W == 1.0f );
}

bool AoVector4::IsZero( ) const
{
	return ( X == 0.0f ) && ( Y == 0.0f ) && ( Z == 0.0f ) && ( W == 0.0f );
}

bool AoVector4::IsPoint( ) const
{
	return ( W == 1.0f );
}

float Dot3( const AoVector4 & Left, const AoVector4 & Right )
{
	return ( Left.X * Right.X ) + ( Left.Y * Right.Y ) + ( Left.Z *  Right.Z );
}

float Dot4( const AoVector4 & Left, const AoVector4 & Right )
{
	return ( Left.X * Right.X ) + ( Left.Y * Right.Y ) + ( Left.Z *  Right.Z ) + ( Left.W * Right.W );
}
