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
class AoMatrix4x4;
class AoVector4;
class AoTexture2D;
class AoShader : public AoAsset
{
	friend AoAssetFactory;
private:
	AoShader( std::vector<char>&& CompiledShader );

public:
	~AoShader( );

	ID3DX11EffectTechnique* GetTechniqueByName( const string& PropertyName ) const;
	ID3DX11EffectVariable* GetVariableByName( const string& PropertyName ) const;
	ID3DX11EffectMatrixVariable* GetMatrixByName( const string& PropertyName ) const;
	ID3DX11EffectScalarVariable* GetScalarByName( const string& PropertyName ) const;
	ID3DX11EffectVectorVariable* GetVectorByName( const string& PropertyName ) const;
	ID3DX11EffectShaderResourceVariable* GetTextureByName( const string& PropertyName ) const;

	void SetGlobalVariableByName( const string& PropertyName, const void* Data, uint32_t ByteCount );
	void SetGlobalMatrixByName( const string& PropertyName, const AoMatrix4x4& Matrix );
	void SetGlobalFloatByName( const string& PropertyName, float Value );
	void SetGlobalIntByName( const string& PropertyName, int Value );
	void SetGlobalBoolByName( const string& PropertyName, bool Value );
	void SetGlobalVectorByName( const string& PropertyName, const AoVector4& Vector );
	void SetGlobalTextureByName( const string& PropertyName, const AoTexture2D* Texture );

	bool IsValidProperty( const string& PropertyName ) const;

private:
	ID3DX11Effect* FX;

};