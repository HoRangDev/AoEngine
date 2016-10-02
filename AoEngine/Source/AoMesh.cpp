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
		D3D11_BUFFER_DESC VBD;
		VBD.Usage = D3D11_USAGE_IMMUTABLE;
		VBD.ByteWidth = sizeof( AoVertex::AoBasic32 ) * Vertices.size( );
		VBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		VBD.CPUAccessFlags = 0;
		VBD.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA VBInitData;
		VBInitData.pSysMem = &Vertices[ 0 ];
		Device->CreateBuffer( &VBD, &VBInitData, &VB );

		D3D11_BUFFER_DESC IBD;
		IBD.Usage = D3D11_USAGE_IMMUTABLE;
		IBD.ByteWidth = sizeof( unsigned int ) * Indices.size( );
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
