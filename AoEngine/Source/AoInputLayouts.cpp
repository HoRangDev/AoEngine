#include "AoInputLayouts.h"
#include "AoAssetManager.h"
#include "AoMaterial.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include <assert.h>

const D3D11_INPUT_ELEMENT_DESC AoInputLayouts::GenericDesc[ 6 ] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 60, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

ID3D11InputLayout* AoInputLayouts::GenericVertexLayout = nullptr;

void AoInputLayouts::Initialize( )
{
	ID3D11Device* Device = AoApplication::GetRenderer( ).GetDevice( );
	assert( Device != nullptr );

	AoMaterial* BasicMaterial = dynamic_cast< AoMaterial* >( AoAssetManager::GetInstance( ).LoadAsset( TEXT( "Shaders" ), TEXT( "Basic" ), TEXT( ".fx" ) ) );
	if ( BasicMaterial != nullptr )
	{
		D3DX11_PASS_DESC PassDesc;
		auto Pass = BasicMaterial->GetTechniqueByName( TEXT( "Basic" ) )->GetPassByIndex( 0 );
		if ( Pass != nullptr )
		{
			Pass->GetDesc( &PassDesc );
			Device->CreateInputLayout( GenericDesc, 6, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &GenericVertexLayout );

			if ( GenericVertexLayout == nullptr )
			{
				// Log Error
			}
		}
		else
		{
			// Log Error
		}
	}
	else
	{
		// Log Error
	}
}

void AoInputLayouts::DeInitialize( )
{
	ReleaseCOM( GenericVertexLayout );
}

ID3D11InputLayout* AoInputLayouts::GetGenericVertexLayout( )
{
	return GenericVertexLayout;
}