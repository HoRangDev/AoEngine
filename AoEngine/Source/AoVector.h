#pragma once

class AoVector
{
public:
	AoVector( float X, float Y, float Z );
	AoVector();

	AoVector operator+( float Operand );
	AoVector operator+( const AoVector& Operand );
	AoVector& operator+=( float Operand );
	AoVector& operator+=( const AoVector& Operand );
	AoVector operator-( float Operand );
	AoVector operator-( const AoVector& Operand );
	AoVector& operator-=( float Operand );
	AoVector& operator-=( const AoVector& Operand );
	AoVector operator*( float Operand );
	AoVector operator*( const AoVector& Operand );
	AoVector& operator*=( float Operand );
	AoVector& operator*=( const AoVector& Operand );
	AoVector operator/( float Operand );
	AoVector operator/( const AoVector& Operand );
	AoVector& operator/=( float Operand );
	AoVector& operator/=( const AoVector& Operand );

	/** | is dot product. */
	float operator|( const AoVector& Operand );

	/** ^ is cross product. */
	AoVector operator^( const AoVector& Operand );

	void SetX( float X );
	float GetX() const;
	void SetY( float Y );
	float GetY() const;
	void SetZ( float Z );
	float GetZ() const;

	float Magnitude() const;
	float SquaredMagnitude() const;

	void Normalize();
	AoVector GetNormalized() const;
	bool IsNormalized() const;

	bool IsOne() const;
	bool IsZero() const;

public:
	float X;
	float Y;
	float Z;

public:
	static AoVector Zero;
	static AoVector One;

};