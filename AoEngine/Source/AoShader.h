#pragma once
#include "AoAsset.h"
#include "AoString.h"
#include <vector>

class ID3DX11Effect;
class ID3DX11EffectTechnique;
class ID3DX11EffectVariable;
class ID3DX11EffectMatrixVariable;
class ID3DX11EffectScalarVariable;
class ID3DX11EffectVectorVariable;
class ID3DX11EffectShaderResourceVariable;
class AoShader : public AoAsset
{
	friend AoAssetFactory;
private:
	AoShader( std::vector<char>&& CompiledShader );

public:
	~AoShader( );

	ID3DX11EffectTechnique* GetTechniqueByName( const string& PropertyName );
	ID3DX11EffectVariable* GetVariableByName( const string& PropertyName );
	ID3DX11EffectMatrixVariable* GetMatrixByName( const string& PropertyName );
	ID3DX11EffectScalarVariable* GetScalarByName( const string& PropertyName );
	ID3DX11EffectVectorVariable* GetVectorByName( const string& PropertyName );
	ID3DX11EffectShaderResourceVariable* GetTextureByName( const string& PropertyName );

private:
	ID3DX11Effect* FX;

};