#pragma once
#include "AoType.h"
#include "DirectXInc.h"
#include "AoGenericVertex.h"
#include <vector>

using VertexVector = std::vector<AoGenericVertex>;
using IndexVector = std::vector<unsigned int>;

class AoMesh
{
public:
	AoMesh( const string& Name );
	~AoMesh( );

	void Initialize( VertexVector&& Vertices, IndexVector&& Indices );
	ID3D11Buffer* GetVertexBuffer( ) const;
	ID3D11Buffer* GetIndexBuffer( ) const;
	string GetName( ) const;

	uint32 GetVertexCount( ) const;
	uint32 GetVertexSize( ) const;
	uint32 GetVerticesSize( ) const;
	uint32 GetIndexCount( ) const;

private:
	string Name;
	ID3D11Buffer* VB;
	ID3D11Buffer* IB;

	uint32 VertexCount;
	uint32 VertexSize;
	uint32 IndexCount;

};