#include "AoMesh.h"
#include "AoApplication.h"
#include "AoRenderer.h"

AoMesh::AoMesh( const string& Name ) 
	: Name( Name )
{
}

AoMesh::~AoMesh( )
{
	ReleaseCOM( VB );
	ReleaseCOM( IB );
}

void AoMesh::Initialize( VertexVector&& Vertices, IndexVector&& Indices )
{
	ID3D11Device* Device = AoApplication::GetRenderer( ).GetDevice( );

	if ( Device != nullptr )
	{
		VertexCount = Vertices.size( );
		VertexSize = sizeof( AoGenericVertex );
		D3D11_BUFFER_DESC VBD;
		VBD.Usage = D3D11_USAGE_IMMUTABLE;
		VBD.ByteWidth = static_cast<unsigned int>( VertexCount * VertexSize );
		VBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		VBD.CPUAccessFlags = 0;
		VBD.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA VBInitData;
		VBInitData.pSysMem = &Vertices[ 0 ];
		Device->CreateBuffer( &VBD, &VBInitData, &VB );

		IndexCount = Indices.size( );

		D3D11_BUFFER_DESC IBD;
		IBD.Usage = D3D11_USAGE_IMMUTABLE;
		IBD.ByteWidth = static_cast<unsigned int>(sizeof( unsigned int ) * IndexCount );
		IBD.BindFlags = D3D11_BIND_INDEX_BUFFER;
		IBD.CPUAccessFlags = 0;
		IBD.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA IBInitData;
		IBInitData.pSysMem = &Indices[ 0 ];
		Device->CreateBuffer( &IBD, &IBInitData, &IB );
	}
}

ID3D11Buffer* AoMesh::GetVertexBuffer( ) const
{
	return VB;
}

ID3D11Buffer* AoMesh::GetIndexBuffer( ) const
{
	return IB;
}

string AoMesh::GetName( ) const
{
	return Name;
}

uint32 AoMesh::GetVertexCount( ) const
{
	return VertexCount;
}

uint32 AoMesh::GetVertexSize( ) const
{
	return VertexSize;
}

uint32 AoMesh::GetVerticesSize( ) const
{
	return GetVertexCount( ) * GetVertexSize( );
}

uint32 AoMesh::GetIndexCount( ) const
{
	return IndexCount;
}
