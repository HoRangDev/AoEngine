#pragma once
#include "AoAsset.h"
#include "DirectXInc.h"

class AoAssetFactory;
class AoTexture2D : public AoAsset
{
	friend AoAssetFactory;
private:
	AoTexture2D( ID3D11ShaderResourceView* SRV );

	ID3D11ShaderResourceView* GetShaderResourceView( ) const;

public:
	~AoTexture2D( );

private:
	ID3D11ShaderResourceView* MapSRV;

};