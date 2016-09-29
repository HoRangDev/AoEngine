#include "AoMatrix4x4.h"
#include "AoMath.h"

AoMatrix4x4 AoMatrix4x4::Identity(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f );

AoMatrix4x4::AoMatrix4x4( float InF ) :
	AoMatrix4x4(
		InF, InF, InF, InF,
		InF, InF, InF, InF,
		InF, InF, InF, InF,
		InF, InF, InF, InF )
{

}

AoMatrix4x4::AoMatrix4x4( float InM11, float InM12, float InM13, float InM14, float InM21, float InM22, float InM23, float InM24, float InM31, float InM32, float InM33, float InM34, float InM41, float InM42, float InM43, float InM44 )
{
	M[ 0 ][ 0 ] = InM11; M[ 0 ][ 1 ] = InM12; M[ 0 ][ 2 ] = InM13; M[ 0 ][ 3 ] = InM14;
	M[ 1 ][ 0 ] = InM21; M[ 1 ][ 1 ] = InM22; M[ 1 ][ 2 ] = InM23; M[ 1 ][ 3 ] = InM24;
	M[ 2 ][ 0 ] = InM31; M[ 2 ][ 1 ] = InM32; M[ 2 ][ 2 ] = InM33; M[ 2 ][ 3 ] = InM34;
	M[ 3 ][ 0 ] = InM41; M[ 3 ][ 1 ] = InM42; M[ 3 ][ 2 ] = InM43; M[ 3 ][ 3 ] = InM44;
}

AoMatrix4x4::AoMatrix4x4( const AoMatrix4x4& InM ) :
	AoMatrix4x4(
		InM.M[ 0 ][ 0 ], InM.M[ 0 ][ 1 ], InM.M[ 0 ][ 2 ], InM.M[ 0 ][ 3 ],
		InM.M[ 1 ][ 0 ], InM.M[ 1 ][ 1 ], InM.M[ 1 ][ 2 ], InM.M[ 1 ][ 3 ],
		InM.M[ 2 ][ 0 ], InM.M[ 2 ][ 1 ], InM.M[ 2 ][ 2 ], InM.M[ 2 ][ 3 ],
		InM.M[ 3 ][ 0 ], InM.M[ 3 ][ 1 ], InM.M[ 3 ][ 2 ], InM.M[ 3 ][ 3 ] )
{

}

AoMatrix4x4& AoMatrix4x4::operator=( float Bias )
{
	M[ 0 ][ 0 ] = M[ 0 ][ 1 ] = M[ 0 ][ 2 ] = M[ 0 ][ 3 ] = Bias;
	M[ 1 ][ 0 ] = M[ 1 ][ 1 ] = M[ 1 ][ 2 ] = M[ 1 ][ 3 ] = Bias;
	M[ 2 ][ 0 ] = M[ 2 ][ 1 ] = M[ 2 ][ 2 ] = M[ 2 ][ 3 ] = Bias;
	M[ 3 ][ 0 ] = M[ 3 ][ 1 ] = M[ 3 ][ 2 ] = M[ 3 ][ 3 ] = Bias;

	return *this;
}

AoMatrix4x4& AoMatrix4x4::operator=( const AoMatrix4x4& InM )
{
	M[ 0 ][ 0 ] = InM.M[ 0 ][ 0 ]; M[ 0 ][ 1 ] = InM.M[ 0 ][ 1 ]; M[ 0 ][ 2 ] = InM.M[ 0 ][ 2 ]; M[ 0 ][ 3 ] = InM.M[ 0 ][ 3 ];
	M[ 1 ][ 0 ] = InM.M[ 1 ][ 0 ]; M[ 1 ][ 1 ] = InM.M[ 1 ][ 1 ]; M[ 1 ][ 2 ] = InM.M[ 1 ][ 2 ]; M[ 1 ][ 3 ] = InM.M[ 1 ][ 3 ];
	M[ 2 ][ 0 ] = InM.M[ 2 ][ 0 ]; M[ 2 ][ 1 ] = InM.M[ 2 ][ 1 ]; M[ 2 ][ 2 ] = InM.M[ 2 ][ 2 ]; M[ 2 ][ 3 ] = InM.M[ 2 ][ 3 ];
	M[ 3 ][ 0 ] = InM.M[ 3 ][ 0 ]; M[ 3 ][ 1 ] = InM.M[ 3 ][ 1 ]; M[ 3 ][ 2 ] = InM.M[ 3 ][ 2 ]; M[ 3 ][ 3 ] = InM.M[ 3 ][ 3 ];

	return *this;
}

AoMatrix4x4 AoMatrix4x4::operator+( float Bias ) const
{
	AoMatrix4x4 Mat( *this );
	Mat.M[ 0 ][ 0 ] += Bias; Mat.M[ 0 ][ 1 ] += Bias; Mat.M[ 0 ][ 2 ] += Bias; Mat.M[ 0 ][ 3 ] += Bias;
	Mat.M[ 1 ][ 0 ] += Bias; Mat.M[ 1 ][ 1 ] += Bias; Mat.M[ 1 ][ 2 ] += Bias; Mat.M[ 1 ][ 3 ] += Bias;
	Mat.M[ 2 ][ 0 ] += Bias; Mat.M[ 2 ][ 1 ] += Bias; Mat.M[ 2 ][ 2 ] += Bias; Mat.M[ 2 ][ 3 ] += Bias;
	Mat.M[ 3 ][ 0 ] += Bias; Mat.M[ 3 ][ 1 ] += Bias; Mat.M[ 3 ][ 2 ] += Bias; Mat.M[ 3 ][ 3 ] += Bias;

	return Mat;
}

AoMatrix4x4 AoMatrix4x4::operator+( const AoMatrix4x4& InM ) const
{
	AoMatrix4x4 Mat( *this );
	Mat.M[ 0 ][ 0 ] += InM.M[ 0 ][ 0 ]; Mat.M[ 0 ][ 1 ] += InM.M[ 0 ][ 1 ]; Mat.M[ 0 ][ 2 ] += InM.M[ 0 ][ 2 ]; Mat.M[ 0 ][ 3 ] += InM.M[ 0 ][ 3 ];
	Mat.M[ 1 ][ 0 ] += InM.M[ 1 ][ 0 ]; Mat.M[ 1 ][ 1 ] += InM.M[ 1 ][ 1 ]; Mat.M[ 1 ][ 2 ] += InM.M[ 1 ][ 2 ]; Mat.M[ 1 ][ 3 ] += InM.M[ 1 ][ 3 ];
	Mat.M[ 2 ][ 0 ] += InM.M[ 2 ][ 0 ]; Mat.M[ 2 ][ 1 ] += InM.M[ 2 ][ 1 ]; Mat.M[ 2 ][ 2 ] += InM.M[ 2 ][ 2 ]; Mat.M[ 2 ][ 3 ] += InM.M[ 2 ][ 3 ];
	Mat.M[ 3 ][ 0 ] += InM.M[ 3 ][ 0 ]; Mat.M[ 3 ][ 1 ] += InM.M[ 3 ][ 1 ]; Mat.M[ 3 ][ 2 ] += InM.M[ 3 ][ 2 ]; Mat.M[ 3 ][ 3 ] += InM.M[ 3 ][ 3 ];

	return Mat;
}

AoMatrix4x4 AoMatrix4x4::operator-( float Bias ) const
{
	AoMatrix4x4 Mat( *this );
	Mat.M[ 0 ][ 0 ] -= Bias; Mat.M[ 0 ][ 1 ] -= Bias; Mat.M[ 0 ][ 2 ] -= Bias; Mat.M[ 0 ][ 3 ] -= Bias;
	Mat.M[ 1 ][ 0 ] -= Bias; Mat.M[ 1 ][ 1 ] -= Bias; Mat.M[ 1 ][ 2 ] -= Bias; Mat.M[ 1 ][ 3 ] -= Bias;
	Mat.M[ 2 ][ 0 ] -= Bias; Mat.M[ 2 ][ 1 ] -= Bias; Mat.M[ 2 ][ 2 ] -= Bias; Mat.M[ 2 ][ 3 ] -= Bias;
	Mat.M[ 3 ][ 0 ] -= Bias; Mat.M[ 3 ][ 1 ] -= Bias; Mat.M[ 3 ][ 2 ] -= Bias; Mat.M[ 3 ][ 3 ] -= Bias;

	return Mat;
}

AoMatrix4x4 AoMatrix4x4::operator-( const AoMatrix4x4& InM ) const
{
	AoMatrix4x4 Mat( *this );
	Mat.M[ 0 ][ 0 ] -= InM.M[ 0 ][ 0 ]; Mat.M[ 0 ][ 1 ] -= InM.M[ 0 ][ 1 ]; Mat.M[ 0 ][ 2 ] -= InM.M[ 0 ][ 2 ]; Mat.M[ 0 ][ 3 ] -= InM.M[ 0 ][ 3 ];
	Mat.M[ 1 ][ 0 ] -= InM.M[ 1 ][ 0 ]; Mat.M[ 1 ][ 1 ] -= InM.M[ 1 ][ 1 ]; Mat.M[ 1 ][ 2 ] -= InM.M[ 1 ][ 2 ]; Mat.M[ 1 ][ 3 ] -= InM.M[ 1 ][ 3 ];
	Mat.M[ 2 ][ 0 ] -= InM.M[ 2 ][ 0 ]; Mat.M[ 2 ][ 1 ] -= InM.M[ 2 ][ 1 ]; Mat.M[ 2 ][ 2 ] -= InM.M[ 2 ][ 2 ]; Mat.M[ 2 ][ 3 ] -= InM.M[ 2 ][ 3 ];
	Mat.M[ 3 ][ 0 ] -= InM.M[ 3 ][ 0 ]; Mat.M[ 3 ][ 1 ] -= InM.M[ 3 ][ 1 ]; Mat.M[ 3 ][ 2 ] -= InM.M[ 3 ][ 2 ]; Mat.M[ 3 ][ 3 ] -= InM.M[ 3 ][ 3 ];

	return Mat;
}

AoMatrix4x4 AoMatrix4x4::operator*( float Scale ) const
{
	AoMatrix4x4 Mat( *this );
	Mat.M[ 0 ][ 0 ] *= Scale; Mat.M[ 0 ][ 1 ] *= Scale; Mat.M[ 0 ][ 2 ] *= Scale; Mat.M[ 0 ][ 3 ] *= Scale;
	Mat.M[ 1 ][ 0 ] *= Scale; Mat.M[ 1 ][ 1 ] *= Scale; Mat.M[ 1 ][ 2 ] *= Scale; Mat.M[ 1 ][ 3 ] *= Scale;
	Mat.M[ 2 ][ 0 ] *= Scale; Mat.M[ 2 ][ 1 ] *= Scale; Mat.M[ 2 ][ 2 ] *= Scale; Mat.M[ 2 ][ 3 ] *= Scale;
	Mat.M[ 3 ][ 0 ] *= Scale; Mat.M[ 3 ][ 1 ] *= Scale; Mat.M[ 3 ][ 2 ] *= Scale; Mat.M[ 3 ][ 3 ] *= Scale;

	return Mat;
}

AoVector4 AoMatrix4x4::operator*( const AoVector4& InV ) const
{
	AoVector4 Vector;
	Vector.X = ( M[ 0 ][ 0 ] * InV.X ) + ( M[ 0 ][ 1 ] * InV.Y ) + ( M[ 0 ][ 2 ] * InV.Z ) + ( M[ 0 ][ 3 ] * InV.W );
	Vector.Y = ( M[ 1 ][ 0 ] * InV.X ) + ( M[ 1 ][ 1 ] * InV.Y ) + ( M[ 1 ][ 2 ] * InV.Z ) + ( M[ 1 ][ 3 ] * InV.W );
	Vector.Z = ( M[ 2 ][ 0 ] * InV.X ) + ( M[ 2 ][ 1 ] * InV.Y ) + ( M[ 2 ][ 2 ] * InV.Z ) + ( M[ 2 ][ 3 ] * InV.W );
	Vector.W = ( M[ 3 ][ 0 ] * InV.X ) + ( M[ 3 ][ 1 ] * InV.Y ) + ( M[ 3 ][ 2 ] * InV.Z ) + ( M[ 3 ][ 3 ] * InV.W );
	return Vector;
}

AoMatrix4x4 AoMatrix4x4::operator*( const AoMatrix4x4& InM ) const
{
	AoMatrix4x4 Mat;
	Mat.M[ 0 ][ 0 ] = ( M[ 0 ][ 0 ] * InM.M[ 0 ][ 0 ] ) + ( M[ 0 ][ 1 ] * InM.M[ 1 ][ 0 ] ) + ( M[ 0 ][ 2 ] * InM.M[ 2 ][ 0 ] ) + ( M[ 0 ][ 3 ] * InM.M[ 3 ][ 0 ] );
	Mat.M[ 0 ][ 1 ] = ( M[ 0 ][ 0 ] * InM.M[ 0 ][ 1 ] ) + ( M[ 0 ][ 1 ] * InM.M[ 1 ][ 1 ] ) + ( M[ 0 ][ 2 ] * InM.M[ 2 ][ 1 ] ) + ( M[ 0 ][ 3 ] * InM.M[ 3 ][ 1 ] );
	Mat.M[ 0 ][ 2 ] = ( M[ 0 ][ 0 ] * InM.M[ 0 ][ 2 ] ) + ( M[ 0 ][ 1 ] * InM.M[ 1 ][ 2 ] ) + ( M[ 0 ][ 2 ] * InM.M[ 2 ][ 2 ] ) + ( M[ 0 ][ 3 ] * InM.M[ 3 ][ 2 ] );
	Mat.M[ 0 ][ 3 ] = ( M[ 0 ][ 0 ] * InM.M[ 0 ][ 3 ] ) + ( M[ 0 ][ 1 ] * InM.M[ 1 ][ 3 ] ) + ( M[ 0 ][ 2 ] * InM.M[ 2 ][ 3 ] ) + ( M[ 0 ][ 3 ] * InM.M[ 3 ][ 3 ] );

	Mat.M[ 1 ][ 0 ] = ( M[ 1 ][ 0 ] * InM.M[ 0 ][ 0 ] ) + ( M[ 1 ][ 1 ] * InM.M[ 1 ][ 0 ] ) + ( M[ 1 ][ 2 ] * InM.M[ 2 ][ 0 ] ) + ( M[ 1 ][ 3 ] * InM.M[ 3 ][ 0 ] );
	Mat.M[ 1 ][ 1 ] = ( M[ 1 ][ 0 ] * InM.M[ 0 ][ 1 ] ) + ( M[ 1 ][ 1 ] * InM.M[ 1 ][ 1 ] ) + ( M[ 1 ][ 2 ] * InM.M[ 2 ][ 1 ] ) + ( M[ 1 ][ 3 ] * InM.M[ 3 ][ 1 ] );
	Mat.M[ 1 ][ 2 ] = ( M[ 1 ][ 0 ] * InM.M[ 0 ][ 2 ] ) + ( M[ 1 ][ 1 ] * InM.M[ 1 ][ 2 ] ) + ( M[ 1 ][ 2 ] * InM.M[ 2 ][ 2 ] ) + ( M[ 1 ][ 3 ] * InM.M[ 3 ][ 2 ] );
	Mat.M[ 1 ][ 3 ] = ( M[ 1 ][ 0 ] * InM.M[ 0 ][ 3 ] ) + ( M[ 1 ][ 1 ] * InM.M[ 1 ][ 3 ] ) + ( M[ 1 ][ 2 ] * InM.M[ 2 ][ 3 ] ) + ( M[ 1 ][ 3 ] * InM.M[ 3 ][ 3 ] );

	Mat.M[ 2 ][ 0 ] = ( M[ 2 ][ 0 ] * InM.M[ 0 ][ 0 ] ) + ( M[ 2 ][ 1 ] * InM.M[ 1 ][ 0 ] ) + ( M[ 2 ][ 2 ] * InM.M[ 2 ][ 0 ] ) + ( M[ 2 ][ 3 ] * InM.M[ 3 ][ 0 ] );
	Mat.M[ 2 ][ 1 ] = ( M[ 2 ][ 0 ] * InM.M[ 0 ][ 1 ] ) + ( M[ 2 ][ 1 ] * InM.M[ 1 ][ 1 ] ) + ( M[ 2 ][ 2 ] * InM.M[ 2 ][ 1 ] ) + ( M[ 2 ][ 3 ] * InM.M[ 3 ][ 1 ] );
	Mat.M[ 2 ][ 2 ] = ( M[ 2 ][ 0 ] * InM.M[ 0 ][ 2 ] ) + ( M[ 2 ][ 1 ] * InM.M[ 1 ][ 2 ] ) + ( M[ 2 ][ 2 ] * InM.M[ 2 ][ 2 ] ) + ( M[ 2 ][ 3 ] * InM.M[ 3 ][ 2 ] );
	Mat.M[ 2 ][ 3 ] = ( M[ 2 ][ 0 ] * InM.M[ 0 ][ 3 ] ) + ( M[ 2 ][ 1 ] * InM.M[ 1 ][ 3 ] ) + ( M[ 2 ][ 2 ] * InM.M[ 2 ][ 3 ] ) + ( M[ 2 ][ 3 ] * InM.M[ 3 ][ 3 ] );

	Mat.M[ 3 ][ 0 ] = ( M[ 3 ][ 0 ] * InM.M[ 0 ][ 0 ] ) + ( M[ 3 ][ 1 ] * InM.M[ 1 ][ 0 ] ) + ( M[ 3 ][ 2 ] * InM.M[ 2 ][ 0 ] ) + ( M[ 3 ][ 3 ] * InM.M[ 3 ][ 0 ] );
	Mat.M[ 3 ][ 1 ] = ( M[ 3 ][ 0 ] * InM.M[ 0 ][ 1 ] ) + ( M[ 3 ][ 1 ] * InM.M[ 1 ][ 1 ] ) + ( M[ 3 ][ 2 ] * InM.M[ 2 ][ 1 ] ) + ( M[ 3 ][ 3 ] * InM.M[ 3 ][ 1 ] );
	Mat.M[ 3 ][ 2 ] = ( M[ 3 ][ 0 ] * InM.M[ 0 ][ 2 ] ) + ( M[ 3 ][ 1 ] * InM.M[ 1 ][ 2 ] ) + ( M[ 3 ][ 2 ] * InM.M[ 2 ][ 2 ] ) + ( M[ 3 ][ 3 ] * InM.M[ 3 ][ 2 ] );
	Mat.M[ 3 ][ 3 ] = ( M[ 3 ][ 0 ] * InM.M[ 0 ][ 3 ] ) + ( M[ 3 ][ 1 ] * InM.M[ 1 ][ 3 ] ) + ( M[ 3 ][ 2 ] * InM.M[ 2 ][ 3 ] ) + ( M[ 3 ][ 3 ] * InM.M[ 3 ][ 3 ] );

	return Mat;
}

AoMatrix4x4 AoMatrix4x4::operator/( float Scale ) const
{
	AoMatrix4x4 Mat( *this );
	Mat.M[ 0 ][ 0 ] /= Scale; Mat.M[ 0 ][ 1 ] /= Scale; Mat.M[ 0 ][ 2 ] /= Scale; Mat.M[ 0 ][ 3 ] /= Scale;
	Mat.M[ 1 ][ 0 ] /= Scale; Mat.M[ 1 ][ 1 ] /= Scale; Mat.M[ 1 ][ 2 ] /= Scale; Mat.M[ 1 ][ 3 ] /= Scale;
	Mat.M[ 2 ][ 0 ] /= Scale; Mat.M[ 2 ][ 1 ] /= Scale; Mat.M[ 2 ][ 2 ] /= Scale; Mat.M[ 2 ][ 3 ] /= Scale;
	Mat.M[ 3 ][ 0 ] /= Scale; Mat.M[ 3 ][ 1 ] /= Scale; Mat.M[ 3 ][ 2 ] /= Scale; Mat.M[ 3 ][ 3 ] /= Scale;

	return Mat;
}

std::ostream& operator<<( std::ostream& Os, const AoMatrix4x4& InM )
{
	Os << InM.M[ 0 ][ 0 ] << '	' << InM.M[ 0 ][ 1 ] << '	' << InM.M[ 0 ][ 2 ] << '	' << InM.M[ 0 ][ 3 ] << std::endl;
	Os << InM.M[ 1 ][ 0 ] << '	' << InM.M[ 1 ][ 1 ] << '	' << InM.M[ 1 ][ 2 ] << '	' << InM.M[ 1 ][ 3 ] << std::endl;
	Os << InM.M[ 2 ][ 0 ] << '	' << InM.M[ 2 ][ 1 ] << '	' << InM.M[ 2 ][ 2 ] << '	' << InM.M[ 2 ][ 3 ] << std::endl;
	Os << InM.M[ 3 ][ 0 ] << '	' << InM.M[ 3 ][ 1 ] << '	' << InM.M[ 3 ][ 2 ] << '	' << InM.M[ 3 ][ 3 ] << std::endl;

	return Os;
}