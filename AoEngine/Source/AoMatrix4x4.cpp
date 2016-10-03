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

AoMatrix4x4 AoMatrix4x4::CreateTranslationMatrix( AoVector Position )
{
	return AoMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		Position.X, Position.Y, Position.Z, 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreateTranslationMatrix( float X, float Y, float Z )
{
	return AoMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		X, Y, Z, 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreateScaleMatrix( AoVector Scale )
{
	return AoMatrix4x4(
		Scale.X, 0.0f, 0.0f, 0.0f,
		0.0f, Scale.Y, 0.0f, 0.0f,
		0.0f, 0.0f, Scale.Z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreateScaleMatrix( float X, float Y, float Z )
{
	return AoMatrix4x4(
		X, 0.0f, 0.0f, 0.0f,
		0.0f, Y, 0.0f, 0.0f,
		0.0f, 0.0f, Z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreateRotationX( float Degree )
{
	float CosDegree = DegreeCos( Degree );
	float SinDegree = DegreeSin( Degree );
	return AoMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, CosDegree, SinDegree, 0.0f,
		0.0f, -SinDegree, CosDegree, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreateRotationY( float Degree )
{
	float CosDegree = DegreeCos( Degree );
	float SinDegree = DegreeSin( Degree );
	return AoMatrix4x4(
		CosDegree, 0.0f, -SinDegree, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		SinDegree, 0.0f, CosDegree, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreateRotationZ( float Degree )
{
	float CosDegree = DegreeCos( Degree );
	float SinDegree = DegreeSin( Degree );
	return AoMatrix4x4(
		CosDegree, SinDegree, 0.0f, 0.0f,
		-SinDegree, CosDegree, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreateRotation( AoVector Degrees )
{
	return CreateRotationZ( Degrees.Z ) * CreateRotationY( Degrees.Y ) * CreateRotationX( Degrees.X );
}

AoMatrix4x4 AoMatrix4x4::CreateTranspose( const AoMatrix4x4& InM )
{
	return AoMatrix4x4(
		InM.M[ 0 ][ 0 ], InM.M[ 1 ][ 0 ], InM.M[ 2 ][ 0 ], InM.M[ 3 ][ 0 ],
		InM.M[ 0 ][ 1 ], InM.M[ 1 ][ 1 ], InM.M[ 2 ][ 1 ], InM.M[ 3 ][ 1 ],
		InM.M[ 0 ][ 2 ], InM.M[ 1 ][ 2 ], InM.M[ 2 ][ 2 ], InM.M[ 3 ][ 2 ],
		InM.M[ 0 ][ 3 ], InM.M[ 1 ][ 3 ], InM.M[ 2 ][ 3 ], InM.M[ 3 ][ 3 ] );
}

AoMatrix4x4 AoMatrix4x4::CreateLookToLH( const AoVector& CameraPosition, const AoVector& CameraDirection, const AoVector& UpDirection )
{
	AoVector Up( UpDirection );
	AoVector ZAxis( CameraDirection );
	ZAxis.Normalize( );
	AoVector XAxis( Up ^ ZAxis );
	XAxis.Normalize( );
	AoVector YAxis( ZAxis ^ XAxis );
	YAxis.Normalize( );

	return AoMatrix4x4(
		XAxis.X, YAxis.X, ZAxis.X, 0.0f,
		XAxis.Y, YAxis.Y, ZAxis.Y, 0.0f,
		XAxis.Z, YAxis.Z, ZAxis.Z, 0.0f,
		-( XAxis | CameraPosition ), -( YAxis | CameraPosition ), -( ZAxis | CameraPosition ), 1.0f );
}

AoMatrix4x4 AoMatrix4x4::CreatePerspectiveLH( float FOV, float AspectRatio, float Near, float Far )
{
	float SinFOV = sin(0.5f * FOV);
	float CosFOV = cos(0.5f * FOV);

	float Height = CosFOV / SinFOV;
	float Width = Height / AspectRatio;
	float Range = Far / ( Far - Near );

	return AoMatrix4x4(
		Width, 0.0f, 0.0f, 0.0f,
		0.0f, Height, 0.0f, 0.0f,
		0.0f, 0.0f, Range, 1.0f,
		0.0f, 0.0f, -Range * Near, 0.0f );
}

DirectX::XMMATRIX AoMatrix4x4::AoMatrixToXMMATRIX( const AoMatrix4x4& InM )
{
	return DirectX::XMMATRIX(
		InM.M[ 0 ][ 0 ], InM.M[ 0 ][ 1 ], InM.M[ 0 ][ 2 ], InM.M[ 0 ][ 3 ],
		InM.M[ 1 ][ 0 ], InM.M[ 1 ][ 1 ], InM.M[ 1 ][ 2 ], InM.M[ 1 ][ 3 ],
		InM.M[ 2 ][ 0 ], InM.M[ 2 ][ 1 ], InM.M[ 2 ][ 2 ], InM.M[ 2 ][ 3 ],
		InM.M[ 3 ][ 0 ], InM.M[ 3 ][ 1 ], InM.M[ 3 ][ 2 ], InM.M[ 3 ][ 3 ] );
}

std::ostream& operator<<( std::ostream& OS, const AoMatrix4x4& InM )
{
	OS << InM.M[ 0 ][ 0 ] << '	' << InM.M[ 0 ][ 1 ] << '	' << InM.M[ 0 ][ 2 ] << '	' << InM.M[ 0 ][ 3 ] << std::endl;
	OS << InM.M[ 1 ][ 0 ] << '	' << InM.M[ 1 ][ 1 ] << '	' << InM.M[ 1 ][ 2 ] << '	' << InM.M[ 1 ][ 3 ] << std::endl;
	OS << InM.M[ 2 ][ 0 ] << '	' << InM.M[ 2 ][ 1 ] << '	' << InM.M[ 2 ][ 2 ] << '	' << InM.M[ 2 ][ 3 ] << std::endl;
	OS << InM.M[ 3 ][ 0 ] << '	' << InM.M[ 3 ][ 1 ] << '	' << InM.M[ 3 ][ 2 ] << '	' << InM.M[ 3 ][ 3 ] << std::endl;

	return OS;
}