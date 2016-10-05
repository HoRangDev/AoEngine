#pragma once
#include "AoVector.h"
#include "AoVector2.h"
#include "AoVector4.h"

struct AoGenericVertex
{
public:
	AoGenericVertex(
		const AoVector& Position = AoVector::Zero,
		const AoVector& Normal = AoVector::Zero,
		const AoVector2& TextureUV = AoVector2::Zero,
		const AoVector& Tangent = AoVector::Zero,
		const AoVector& BiNormal = AoVector::Zero,
		const AoVector4& Color = AoVector4::One);

public:
	AoVector	Position;	// X, Y, Z		,	Semantic: POSITION	,	ByteOffset: 0
	AoVector	Normal;		// X, Y, Z		,	Semantic: NORMAL	,	ByteOffset: 12
	AoVector4	Color;		// R, G, B, A	,	Semantic: COLOR		,	BytePffset: 24
	AoVector2	TextureUV;	// U, V			,	Semantic: TEXCOORD	,	ByteOffset: 40
	AoVector	Tangent;	// X, Y, Z		,	Semantic: TANGENT	,	ByteOffset: 48
	AoVector	BiNormal;	// X, Y, Z		,	Semantic: BINORMAL	,	ByteOffset: 60
							//											ByteOffset: 72

};