#pragma once
#include "AoAsset.h"
#include "DirectXInc.h"

class AoAssetFactory;
class AoTexture2DAsset : public AoAsset
{
	friend AoAssetFactory;
private:
	AoTexture2DAsset( ID3D11ShaderResourceView* SRV );

	ID3D11ShaderResourceView* GetShaderResourceView( ) const;

public:
	~AoTexture2DAsset( );

private:
	ID3D11ShaderResourceView* MapSRV;

};