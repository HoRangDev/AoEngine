#pragma once
#include "AoType.h"
#include "AoVector4.h"

class AoMaterialData
{
public:
	AoMaterialData( );
	AoMaterialData( const AoVector4& Ambient, const AoVector4& Diffuse, const AoVector4& Specular, const AoVector4& Emissive );

	AoVector4 GetAmbient( ) const;
	void SetAmbient( const AoVector4& Ambient );

	AoVector4 GetDiffuse( ) const;
	void SetDiffuse( const AoVector4& Diffuse );

	AoVector4 GetSpecular( ) const;
	void SetSpecular( const AoVector4& Specular );

	AoVector4 GetEmissive( ) const;
	void SetEmissive( const AoVector4& Emissive );

private:
	AoVector4 Ambient;				// ¡÷∫Ø±§
	AoVector4 Diffuse;				// »ÆªÍ(ªÍ∂ı)±§
	AoVector4 Specular;				// π›ªÁ±§
	AoVector4 Emissive;				// πÊªÁ±§

};