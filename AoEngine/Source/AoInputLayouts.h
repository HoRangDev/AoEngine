#pragma once
#include "DirectXInc.h"
#include "AoGenericVertex.h"

class AoInputLayouts
{
public:
	static void Initialize( );
	static void DeInitialize( );

	static ID3D11InputLayout* GetGenericVertexLayout( );

private:
	static const D3D11_INPUT_ELEMENT_DESC GenericDesc[ 6 ];
	static ID3D11InputLayout* GenericVertexLayout;

};