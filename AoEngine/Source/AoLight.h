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
	AoVector4 Ambient;			// �ֺ���
	AoVector4 Diffuse;			// Ȯ��(���)��
	AoVector  Specular;			// �ݻ籤
	float	  SpecularExponent; // �ݻ籤 ����

	AoVector Position;			// ������ ��ġ
	float Range;				// ������ ��ġ�� ����(�Ÿ�)

	AoVector Direction;			// ������ ����
	float SpotExponent;			// ���� ����

	float ConstantAttenuation;	// ��� ���� ���
	float LinearAttenuation;	// ���� ���� ���
	float QuadraticAttenuation; // ���� ���� ���
	ELightType LightType;		// ���� ����

};