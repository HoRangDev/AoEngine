#include "AoGenericVertex.h"

AoGenericVertex::AoGenericVertex( const AoVector & Position, const AoVector & Normal, const AoVector2 & TextureUV, const AoVector & Tangent, const AoVector & BiNormal, const AoVector4 & Color )
	: 
	Position( Position ),
	Normal( Normal ),
	TextureUV( TextureUV ),
	Tangent( Tangent ),
	BiNormal( BiNormal ),
	Color( Color )

{
}
