#pragma once

class AoVector2
{
public:
	AoVector2( float X = 0.0f, float Y = 0.0f );

	AoVector2& operator=( const AoVector2& Operand );
	AoVector2 operator+( float Operand );
	AoVector2 operator+( const AoVector2& Operand );
	AoVector2& operator+=( float Operand );
	AoVector2& operator+=( const AoVector2& Operand );
	AoVector2 operator-( float Operand );
	AoVector2 operator-( const AoVector2& Operand );
	AoVector2& operator-=( float Operand );
	AoVector2& operator-=( const AoVector2& Operand );
	AoVector2 operator*( float Operand );
	AoVector2 operator*( const AoVector2& Operand );
	AoVector2& operator*=( float Operand );
	AoVector2& operator*=( const AoVector2& Operand );
	AoVector2 operator/( float Operand );
	AoVector2 operator/( const AoVector2& Operand );
	AoVector2& operator/=( float Operand );
	AoVector2& operator/=( const AoVector2& Operand );

	/** | is dot product. */
	float operator|( const AoVector2& Operand );

	void SetX( float X );
	float GetX( ) const;
	void SetY( float Y );
	float GetY( ) const;

	float Size( ) const;
	float SquaredSize( ) const;

	void Normalize( );
	AoVector2 GetNormal( ) const;

	bool IsUnit( ) const;
	bool IsOne( ) const;
	bool IsZero( ) const;

public:
	float X;
	float Y;

public:
	static const AoVector2 Zero;
	static const AoVector2 One;

};