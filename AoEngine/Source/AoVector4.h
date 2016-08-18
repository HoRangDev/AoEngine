#pragma once

class AoVector4
{
public:
	AoVector4( float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 0.0f );

	AoVector4& operator=( const AoVector4& Operand );
	AoVector4 operator+( float Operand );
	AoVector4 operator+( const AoVector4& Operand );
	AoVector4& operator+=( float Operand );
	AoVector4& operator+=( const AoVector4& Operand );
	AoVector4 operator-( float Operand );
	AoVector4 operator-( const AoVector4& Operand );
	AoVector4& operator-=( float Operand );
	AoVector4& operator-=( const AoVector4& Operand );
	AoVector4 operator*( float Operand );
	AoVector4 operator*( const AoVector4& Operand );
	AoVector4& operator*=( float Operand );
	AoVector4& operator*=( const AoVector4& Operand );
	AoVector4 operator/( float Operand );
	AoVector4 operator/( const AoVector4& Operand );
	AoVector4& operator/=( float Operand );
	AoVector4& operator/=( const AoVector4& Operand );

	/** | is dot4 product. */
	float operator|( const AoVector4& Operand );

	/** ^ is cross product. */
	AoVector4 operator^( const AoVector4& Operand );

	void SetX( float X );
	float GetX() const;
	void SetY( float Y );
	float GetY() const;
	void SetZ( float Z );
	float GetZ() const;
	void SetW( float W );
	float GetW() const;

	float Size3() const;
	float SquaredSize3() const;

	float Size4() const;
	float SquaredSize4() const;

	friend float Dot3( const AoVector4& Left, const AoVector4& Right );
	friend float Dot4( const AoVector4& Left, const AoVector4& Right );

	void Normalize3();
	AoVector4 GetNormal3() const;

	bool IsUnit() const;
	bool IsOne() const;
	bool IsZero() const;
	bool IsPoint() const;

public:
	float X;
	float Y;
	float Z;
	float W;

};