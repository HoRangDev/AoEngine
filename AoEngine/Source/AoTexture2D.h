#pragma once
#include "AoAsset.h"
#include "DirectXInc.h"

class AoAssetFactory;
class AoTexture2D : public AoAsset
{
	friend AoAssetFactory;
private:
	AoTexture2D( ID3D11ShaderResourceView* SRV );

public:
	~AoTexture2D( );

	ID3D11ShaderResourceView* GetShaderResourceView( ) const;

private:
	ID3D11ShaderResourceView* MapSRV;

};