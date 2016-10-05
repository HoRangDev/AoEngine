#pragma once
#include "AoType.h"
#include "AoVector.h"
#include "AoVector4.h"

enum class ELightType : int32
{
	Directional = 0,
	Point		= 1,
	Spot		= 2
};

class AoLight
{
public:
	AoLight( );

	AoVector4 GetAmbient( ) const;
	void SetAmbient( const AoVector4& Ambient );

	AoVector4 GetDiffuse( ) const;
	void SetDiffuse( const AoVector4& Diffuse );

	AoVector GetSpecular( ) const;
	void SetSpecular( const AoVector& Specular );

	float GetSpecularExponent( ) const;
	void SetSpecularExponent( float Exponent );

	AoVector GetPosition( ) const;
	void SetPosition( const AoVector& Position );

	float GetRange( ) const;
	void SetRange( float Range );

	AoVector GetDirection( ) const;
	void SetDirection( const AoVector& Direction );

	float GetSpotExponent( ) const;
	void SetSpotExponent( float Exponent );

	float GetConstantAttenuation( ) const;
	void SetConstantAttenuation( float Value );

	float GetLinearAttenuation( ) const;
	void SetLinearAttenuation( float Value );

	float GetQuadraticAttenuation( ) const;
	void SetQuadraticAttenuation( float Value );

	ELightType GetLightType( ) const;
	void SetLightType( ELightType Type );

private:
	AoVector4 Ambient;			// 주변광
	AoVector4 Diffuse;			// 확산(산란)광
	AoVector  Specular;			// 반사광
	float	  SpecularExponent; // 반사광 지수

	AoVector Position;			// 광원의 위치
	float Range;				// 광원이 미치는 범위(거리)

	AoVector Direction;			// 광원의 방향
	float SpotExponent;			// 점광 지수

	float ConstantAttenuation;	// 상수 감쇠 계수
	float LinearAttenuation;	// 일차 감쇠 계수
	float QuadraticAttenuation; // 이차 감쇠 계수
	ELightType LightType;		// 광원 종류

};