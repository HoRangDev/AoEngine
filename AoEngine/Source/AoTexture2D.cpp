#include "AoTexture2D.h"

AoTexture2D::AoTexture2D( ID3D11ShaderResourceView* SRV )
	: MapSRV( SRV )
{
}

ID3D11ShaderResourceView* AoTexture2D::GetShaderResourceView( ) const
{
	return MapSRV;
}

AoTexture2D::~AoTexture2D( )
{
	ReleaseCOM( MapSRV );
}
