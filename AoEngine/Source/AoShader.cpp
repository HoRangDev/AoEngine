#include "AoShader.h"
#include "AoStringUtility.h"
#include "DirectXInc.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoMatrix4x4.h"
#include "AoVector.h"
#include "AoVector2.h"
#include "AoVector4.h"
#include "AoTexture2D.h"

AoShader::AoShader( std::vector<char>&& CompiledShader ) 
	: FX( nullptr )
{
	ID3D11Device* Device = AoApplication::GetRenderer( ).GetDevice( );
	D3DX11CreateEffectFromMemory( &CompiledShader[ 0 ], CompiledShader.size( ), 0, Device, &FX );
	assert( FX != nullptr );
}

AoShader::~AoShader( )
{
	ReleaseCOM( FX );
}

ID3DX11EffectTechnique * AoShader::GetTechniqueByIndex( uint32 Index )
{
	return FX->GetTechniqueByIndex( Index );
}

ID3DX11EffectTechnique* AoShader::GetTechniqueByName( const string& PropertyName ) const
{
	return FX->GetTechniqueByName( AoStringUtility::WStringToString(PropertyName).c_str() );
}

ID3DX11EffectVariable* AoShader::GetVariableByName( const string& PropertyName ) const
{
	return FX->GetVariableByName( AoStringUtility::WStringToString( PropertyName ).c_str( ) );
}

ID3DX11EffectMatrixVariable* AoShader::GetMatrixByName( const string& PropertyName ) const
{
	return GetVariableByName( PropertyName )->AsMatrix( );
}

ID3DX11EffectScalarVariable* AoShader::GetScalarByName( const string& PropertyName ) const
{
	return GetVariableByName( PropertyName )->AsScalar( );
}

ID3DX11EffectVectorVariable* AoShader::GetVectorByName( const string& PropertyName ) const
{
	return GetVariableByName( PropertyName )->AsVector( );
}

ID3DX11EffectShaderResourceVariable* AoShader::GetTextureByName( const string& PropertyName ) const
{
	return GetVariableByName( PropertyName )->AsShaderResource( );
}

void AoShader::SetGlobalVariableByName( const string& PropertyName, const void* Data, uint32 ByteOffset, uint32 ByteCount )
{
	ID3DX11EffectVariable* Variable = GetVariableByName( PropertyName );
	if( Variable != nullptr )
	{
		if ( Variable->IsValid( ) )
		{
			Variable->SetRawValue( Data, 0, ByteCount );
		}
		ReleaseCOM( Variable );
	}
}

void AoShader::SetGlobalMatrixByName( const string& PropertyName, const AoMatrix4x4& Matrix )
{
	ID3DX11EffectMatrixVariable* Variable = GetMatrixByName( PropertyName );
	if ( Variable != nullptr )
	{
		if ( Variable->IsValid( ) )
		{
			Variable->SetMatrix( reinterpret_cast< const float* >( &Matrix ) );
		}
		ReleaseCOM( Variable );
	}
}

void AoShader::SetGlobalFloatByName( const string& PropertyName, float Value )
{
	ID3DX11EffectScalarVariable* Variable = GetScalarByName( PropertyName );
	if( Variable != nullptr )
	{
		if ( Variable->IsValid( ) )
		{
			Variable->SetFloat( Value );
		}
		ReleaseCOM( Variable );
	}
}

void AoShader::SetGlobalIntByName( const string& PropertyName, int Value )
{
	ID3DX11EffectScalarVariable* Variable = GetScalarByName( PropertyName );
	if( Variable != nullptr )
	{
		if ( Variable->IsValid( ) )
		{
			Variable->SetInt( Value );
		}
		ReleaseCOM( Variable );
	}
}

void AoShader::SetGlobalBoolByName( const string& PropertyName, bool Value )
{
	ID3DX11EffectScalarVariable* Variable = GetScalarByName( PropertyName );
	if( Variable != nullptr )
	{
		if ( Variable->IsValid( ) )
		{
			Variable->SetBool( Value );
		}
		ReleaseCOM( Variable );
	}
}

void AoShader::SetGlobalVectorByName( const string& PropertyName, const AoVector4& Vector )
{
	ID3DX11EffectVectorVariable* Variable = GetVectorByName( PropertyName );
	if( Variable != nullptr )
	{
		if ( Variable->IsValid( ) )
		{
			Variable->SetFloatVector( reinterpret_cast< const float * >( &Vector ) );
		}
		ReleaseCOM( Variable );
	}
}

void  AoShader::SetGlobalTextureByName(const string& PropertyName, const AoTexture2D* Texture )
{
	ID3DX11EffectShaderResourceVariable* Variable = GetTextureByName( PropertyName );
	if( Variable != nullptr )
	{
		if ( Variable->IsValid( ) )
		{
			if ( Texture != nullptr )
			{
				Variable->SetResource( Texture->GetShaderResourceView( ) );
			}
			else
			{
				Variable->SetResource( nullptr );
			}
		}
		ReleaseCOM( Variable );
	}
}

bool AoShader::IsValidProperty( const string& PropertyName ) const
{
	auto Variable = GetVariableByName( PropertyName );
	bool bIsValid = Variable->IsValid( );
	ReleaseCOM( Variable );
	return bIsValid;
}
