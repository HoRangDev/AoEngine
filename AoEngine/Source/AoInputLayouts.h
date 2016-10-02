#pragma once
#include "DirectXInc.h"
#include "AoVertex.h"

class AoInputLayouts
{
public:
	static void Initialize( );
	static void DeInitialize( );

	static ID3D11InputLayout* GetLayout( AoVertex::EAoVertex Type );

private:
	static const D3D11_INPUT_ELEMENT_DESC Basic32Desc[ 3 ];
	static ID3D11InputLayout* Basic32Layout;

};