#include "WindowsInc.h"
#include "AoString.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoShaderAsset.h"
#include "AoAssetFactory.h"
#include "AoModelAsset.h"
#include "AoMesh.h"
#include "AoTexture2DAsset.h"
#include "AoVertex.h"
#include <vector>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>

AoAsset* AoAssetFactory::CreateAsset( const string& AssetDirectoryPath, const string& FilePath, const string& FileName, const string& FileExtension )
{
	AoAsset* CreatedAsset = new AoAsset( );
	string AssetFullPath = AssetDirectoryPath + TEXT( "/" ) + FilePath + FileName + FileExtension;

	SAssetTypeMatchInfo AssetTypeMatchInfo = AoAsset::GetMatchInfoFromFileExtension( FileExtension );
	switch ( AssetTypeMatchInfo.MatchType )
	{
	case EAssetType::Model:
		CreatedAsset = CreateModelFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Texture2D:
		CreatedAsset = CreateTexture2DFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Shader:
		//CreatedAsset = CreateShaderFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Audio:
		//CreatedAsset = CreateAudioFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Text:
		//CreatedAsset = CreateAudioFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Config:
		//CreatedAsset = CreateConfigFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;
	}

	if ( CreatedAsset != nullptr )
	{
		CreatedAsset->SetFilePath( FilePath );
		CreatedAsset->SetFileName( FileName );
		CreatedAsset->SetFileExtension( FileExtension );
	}

	return CreatedAsset;
}

AoModelAsset* AoAssetFactory::CreateModelFromFile( const string& FileFullPath, ESupportAssetExtension Extension )
{
	AoModelAsset* CreatedAsset = nullptr;

	/* Loading From File */
	switch ( Extension )
	{
	case ESupportAssetExtension::FBX:
	case ESupportAssetExtension::OBJ:
		Assimp::Importer Importer;
		const aiScene* Scene = Importer.ReadFile(
			AoString::WStringToString( FileFullPath ),
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices );

		std::vector<AoMesh*> Meshes(Scene->mNumMeshes);
		for ( unsigned int MeshIndex = 0; MeshIndex < Scene->mNumMeshes; ++MeshIndex )
		{
			const aiMesh* Mesh = Scene->mMeshes[ MeshIndex ];

			VertexVector Vertices( Mesh->mNumVertices );
			IndexVector Indices( 3 * Mesh->mNumFaces );
			for ( unsigned int Index = 0; Index < Mesh->mNumVertices; ++Index )
			{
				aiVector3D Position = Mesh->mVertices[ Index ];
				aiVector3D Normal = Mesh->mNormals[ Index ];
				aiVector3D UVW = Mesh->mTextureCoords[ 0 ][ Index ];
				Vertices[ Index ] = AoVertex::AoBasic32(
					AoVector( Position.x, Position.y, Position.z ),
					AoVector( Normal.x, Normal.y, Normal.z ),
					AoVector2( UVW.x, UVW.y ) );
			}

			for ( unsigned int Index = 0; Index < Mesh->mNumFaces; ++Index )
			{
				Indices[ Index + 0 ] = ( Mesh->mFaces[ Index ].mIndices[ 0 ] );
				Indices[ Index + 1 ] = ( Mesh->mFaces[ Index ].mIndices[ 1 ] );
				Indices[ Index + 2 ] = ( Mesh->mFaces[ Index ].mIndices[ 2 ] );
			}

			AoMesh* MeshData = new AoMesh( AoString::StringToWString( Mesh->mName.C_Str( ) ) );
			MeshData->Initialize(
				std::move( Vertices ),
				std::move( Indices ) );
			Meshes[ MeshIndex ] = MeshData;
		}

		CreatedAsset = new AoModelAsset( std::move(Meshes) );
		break;
	}

	return CreatedAsset;
}

AoTexture2DAsset* AoAssetFactory::CreateTexture2DFromFile( const string& FileFullPath, ESupportAssetExtension Extension )
{
	AoTexture2DAsset* CreatedAsset = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;
	ID3D11Device* Device = AoApplication::GetRenderer( ).GetDevice( );

	switch( Extension )
	{
	case ESupportAssetExtension::PNG:
	case ESupportAssetExtension::JPG:
		DirectX::CreateWICTextureFromFile( 
			Device,
			FileFullPath.c_str(),
			nullptr, &SRV );
		break;

	case ESupportAssetExtension::DDS:
		DirectX::CreateDDSTextureFromFile(
			Device,
			FileFullPath.c_str( ),
			nullptr, &SRV );
		break;
	}

	if( SRV != nullptr )
	{
		CreatedAsset = new AoTexture2DAsset( SRV );
	}

	return CreatedAsset;
}
