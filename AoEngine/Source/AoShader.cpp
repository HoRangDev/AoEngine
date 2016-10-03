#include "AoShader.h"
#include "DirectXInc.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoMatrix4x4.h"
#include "AoVector.h"
#include "AoVector2.h"
#include "AoVector4.h"
#include "AoTexture2D.h"

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

ID3DX11EffectMatrixVariable* AoShader::GetMatrixByName( const string& PropertyName )
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

void AoShader::SetGlobalVariableByName( const string& PropertyName, const void* Data, uint32_t ByteCount )
{
	ID3DX11EffectVariable* Variable = GetVariableByName( PropertyName );
	if( Variable != nullptr )
	{
		Variable->SetRawValue( Data, 0, ByteCount );
	}
}

void AoShader::SetGlobalMatrixByName( const string& PropertyName, const AoMatrix4x4& Matrix )
{
	ID3DX11EffectMatrixVariable* Variable = GetMatrixByName( PropertyName );
	if ( Variable != nullptr )
	{
		Variable->SetMatrix( reinterpret_cast< const float* >( &Matrix ) );
	}
}

void AoShader::SetGlobalFloatByName( const string& PropertyName, float Value )
{
	ID3DX11EffectScalarVariable* Variable = GetScalarByName( PropertyName );
	if( Variable != nullptr )
	{
		Variable->SetFloat( Value );
	}
}

void AoShader::SetGlobalIntByName( const string& PropertyName, int Value )
{
	ID3DX11EffectScalarVariable* Variable = GetScalarByName( PropertyName );
	if( Variable != nullptr )
	{
		Variable->SetInt( Value );
	}
}

void AoShader::SetGlobalBoolByName( const string& PropertyName, bool Value )
{
	ID3DX11EffectScalarVariable* Variable = GetScalarByName( PropertyName );
	if( Variable != nullptr )
	{
		Variable->SetBool( Value );
	}
}

void  AoShader::SetGlobalTextureByName(const string& PropertyName, const AoTexture2D* Texture )
{
	ID3DX11EffectShaderResourceVariable* Variable = GetTextureByName( PropertyName );
	if( Variable != nullptr )
	{
		if( Texture != nullptr )
		{
			Variable->SetResource( Texture->GetShaderResourceView( ) );
		}
		else
		{
			Variable->SetResource( nullptr );
		}
	}
}