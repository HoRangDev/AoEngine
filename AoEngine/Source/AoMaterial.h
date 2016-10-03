#pragma once
#include "WindowsInc.h"
#include "AoVector2.h"
#include "AoVector.h"
#include "AoVector4.h"

struct AoMaterial
{
	AoMaterial( )
	{
		ZeroMemory( this, sizeof( AoMaterial ) );
		Ambient = AoVector4::One;
		Diffuse = AoVector4::One;
		Specular = AoVector4::One;
	}

	// Ambient
	AoVector4 Ambient;
	// Diffuse
	AoVector4 Diffuse;
	// Specular, w = Specular exponent
	AoVector4 Specular;
};