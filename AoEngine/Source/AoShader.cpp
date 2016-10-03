#include "AoShader.h"
#include "DirectXInc.h"
#include "AoApplication.h"
#include "AoRenderer.h"

AoShader::AoShader( std::vector<char>&& CompiledShader )
{
	ID3D11Device* Device = AoApplication::GetRenderer( ).GetDevice( );
	D3DX11CreateEffectFromMemory( &CompiledShader[ 0 ], CompiledShader.size( ), 0, Device, &FX );
	assert( FX != nullptr );
}

AoShader::~AoShader( )
{
	ReleaseCOM( FX );
}

ID3DX11EffectTechnique* AoShader::GetTechniqueByName( const string& PropertyName )
{
	return FX->GetTechniqueByName( AoString::WStringToString(PropertyName).c_str() );
}

ID3DX11EffectVariable* AoShader::GetVariableByName( const string& PropertyName )
{
	return FX->GetVariableByName( AoString::WStringToString( PropertyName ).c_str( ) );
}

ID3DX11EffectMatrixVariable * AoShader::GetMatrixByName( const string& PropertyName )
{
	return GetVariableByName( PropertyName )->AsMatrix( );
}

ID3DX11EffectScalarVariable* AoShader::GetScalarByName( const string& PropertyName )
{
	return GetVariableByName( PropertyName )->AsScalar( );
}

ID3DX11EffectVectorVariable* AoShader::GetVectorByName( const string& PropertyName )
{
	return GetVariableByName( PropertyName )->AsVector( );
}

ID3DX11EffectShaderResourceVariable* AoShader::GetTextureByName( const string& PropertyName )
{
	return GetVariableByName( PropertyName )->AsShaderResource( );
}
