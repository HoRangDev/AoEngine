#include "AoTexture2DAsset.h"

AoTexture2DAsset::AoTexture2DAsset( ID3D11ShaderResourceView* SRV ) 
	: MapSRV( SRV )
{
}

ID3D11ShaderResourceView* AoTexture2DAsset::GetShaderResourceView( ) const
{
	return MapSRV;
}

AoTexture2DAsset::~AoTexture2DAsset( )
{
	ReleaseCOM( MapSRV );
}
