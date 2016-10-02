#include <assert.h>
#include "AoInputLayouts.h"
#include "AoApplication.h"
#include "AoRenderer.h"

const D3D11_INPUT_ELEMENT_DESC AoInputLayouts::Basic32Desc[ 3 ] = 
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "TEX1UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

ID3D11InputLayout* AoInputLayouts::Basic32Layout = nullptr;

void AoInputLayouts::Initialize( )
{
	ID3D11Device* Device = AoApplication::GetRenderer( ).GetDevice( );
	assert( Device != nullptr );

#pragma region Basic32 Initialize



#pragma endregion

}

void AoInputLayouts::DeInitialize( )
{
	ReleaseCOM( Basic32Layout );
}

ID3D11InputLayout * AoInputLayouts::GetLayout( AoVertex::EAoVertex Type )
{
	switch( Type )
	{
	case AoVertex::EAoVertex::Basic32:
		return Basic32Layout;
	}

	return nullptr;
}