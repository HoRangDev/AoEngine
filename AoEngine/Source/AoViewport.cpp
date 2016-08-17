#include "AoViewport.h"

AoViewport::AoViewport( float Width, float Height, float TopLeftX, float TopLeftY, float MinDepth, float MaxDepth ) :
	Width(Width),
	Height(Height),
	TopLeftX(TopLeftX),
	TopLeftY(TopLeftY),
	MinDepth(MinDepth),
	MaxDepth(MaxDepth)
{

}

AoViewport::AoViewport() :
	AoViewport( 0, 0 )
{

}
