#include "AoAssetFactory.h"
#include "AoAssetManager.h"
#include "AoString.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoShader.h"
#include "AoMaterial.h"
#include "AoModel.h"
#include "AoMesh.h"
#include "AoTexture2D.h"
#include "AoVertex.h"
#include "WindowsInc.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <tinyxml2.h>

AoAsset* AoAssetFactory::CreateAsset( const string& AssetDirectoryPath, const string& FilePath, const string& FileName, const string& FileExtension )
{
	AoAsset* CreatedAsset = nullptr;
	string AssetFullPath = AssetDirectoryPath + TEXT( "/" ) + FilePath + TEXT( "/" ) + FileName + FileExtension;

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
		CreatedAsset = CreateShaderFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Material:
		CreatedAsset = CreateMaterialFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Audio:
		//CreatedAsset = CreateAudioFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
		break;

	case EAssetType::Text:
		//CreatedAsset = CreateTextFromFile( AssetFullPath, AssetTypeMatchInfo.ExtensionType );
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

AoModel* AoAssetFactory::CreateModelFromFile( const string& FileFullPath, ESupportAssetExtension Extension )
{
	AoModel* CreatedAsset = nullptr;

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

		CreatedAsset = new AoModel( std::move(Meshes) );
		break;
	}

	return CreatedAsset;
}

AoTexture2D* AoAssetFactory::CreateTexture2DFromFile( const string& FileFullPath, ESupportAssetExtension Extension )
{
	AoTexture2D* CreatedAsset = nullptr;
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
		CreatedAsset = new AoTexture2D( SRV );
	}

	return CreatedAsset;
}

AoShader* AoAssetFactory::CreateShaderFromFile( const string& FileFullPath, ESupportAssetExtension Extension )
{
	AoShader* CreatedAsset = nullptr;

	switch ( Extension )
	{
	case ESupportAssetExtension::FXO:
		std::ifstream FileIn( FileFullPath, std::ios::binary );

		if ( FileIn.is_open( ) )
		{
			FileIn.seekg( 0, std::ios_base::end );
			int Size = static_cast< int >( FileIn.tellg( ) );
			FileIn.seekg( 0, std::ios_base::beg );
			std::vector<char> CompiledShader( Size );

			FileIn.read( &CompiledShader[ 0 ], Size );
			FileIn.close( );

			CreatedAsset = new AoShader( std::move( CompiledShader ) );
		}
		break;
	}

	return CreatedAsset;
}

AoMaterial* AoAssetFactory::CreateMaterialFromFile( const string& FileFullPath, ESupportAssetExtension Extension )
{
	AoMaterial* CreatedAsset = nullptr;

	switch ( Extension )
	{
	case ESupportAssetExtension::Material:
		tinyxml2::XMLDocument Document;
		auto Error = Document.LoadFile( AoString::WStringToString( FileFullPath ).c_str( ) );
		if ( Error == tinyxml2::XMLError::XML_SUCCESS )
		{
			tinyxml2::XMLNode* RootNode = Document.FirstChildElement( "Material" );

			if ( RootNode != nullptr )
			{
				tinyxml2::XMLElement* MaterialNameElement =
					RootNode->FirstChildElement( "MaterialName" );

				tinyxml2::XMLElement* UseShaderElement =
					RootNode->FirstChildElement( "UseShaderAsset" );

				bool bIsValidMaterialInfo = ( MaterialNameElement != nullptr && UseShaderElement != nullptr );
				if ( bIsValidMaterialInfo )
				{
					AoShader* UseShader =
						dynamic_cast< AoShader* >(
							AoAssetManager::GetInstance( ).LoadAsset(
							AoString::StringToWString( UseShaderElement->Attribute( "Path" ) ),
							AoString::StringToWString( UseShaderElement->Attribute( "Name" ) ),
							AoString::StringToWString( UseShaderElement->Attribute( "Ext" ) )
							) );

					bool bIsValidShader = UseShader != nullptr;
					if ( bIsValidShader )
					{
						CreatedAsset = new AoMaterial( UseShader );
						CreatedAsset->SetMaterialName( AoString::StringToWString( MaterialNameElement->GetText( ) ) );

						tinyxml2::XMLNode* PropertiesNode = RootNode->FirstChildElement( "Properties" );
						bool bIsHaveProperties = PropertiesNode != nullptr;
						if ( bIsHaveProperties )
						{
							tinyxml2::XMLElement* CurrentProperty =
								PropertiesNode->FirstChildElement( "Property" );
							while ( CurrentProperty != nullptr )
							{
								std::string TypeName =
									AoString::StringToLower( CurrentProperty->Attribute( "Type" ) );
								string PropertyName =
									AoString::StringToWString( CurrentProperty->Attribute( "Name" ) );

								tinyxml2::XMLElement* ValueElement = CurrentProperty->FirstChildElement( "Value" );
								bool bIsValidValue = ValueElement != nullptr;
								if ( bIsValidValue )
								{
									if ( TypeName == "int" )
									{
										CreatedAsset->SetIntByName(
											PropertyName,
											ValueElement->IntAttribute( "Scalar" ) );
									}
									else if ( TypeName == "float" )
									{
										CreatedAsset->SetFloatByName(
											PropertyName,
											ValueElement->FloatAttribute( "Scalar" ) );
									}
									else if ( TypeName == "bool" )
									{
										CreatedAsset->SetBoolByName(
											PropertyName,
											ValueElement->BoolAttribute( "Scalar" ) );
									}
									else if ( TypeName == "vector" )
									{
										CreatedAsset->SetVectorByName(
											PropertyName,
											AoVector4(
											ValueElement->FloatAttribute( "X" ),
											ValueElement->FloatAttribute( "Y" ),
											ValueElement->FloatAttribute( "Z" ),
											ValueElement->FloatAttribute( "W" ) ) );
									}
									else if ( TypeName == "matrix" )
									{
										CreatedAsset->SetMatrixByName(
											PropertyName,
											AoMatrix4x4(
											ValueElement->FloatAttribute( "M11" ), ValueElement->FloatAttribute( "M12" ),
											ValueElement->FloatAttribute( "M13" ), ValueElement->FloatAttribute( "M14" ),

											ValueElement->FloatAttribute( "M21" ), ValueElement->FloatAttribute( "M22" ),
											ValueElement->FloatAttribute( "M23" ), ValueElement->FloatAttribute( "M24" ),

											ValueElement->FloatAttribute( "M31" ), ValueElement->FloatAttribute( "M32" ),
											ValueElement->FloatAttribute( "M33" ), ValueElement->FloatAttribute( "M34" ),

											ValueElement->FloatAttribute( "M41" ), ValueElement->FloatAttribute( "M42" ),
											ValueElement->FloatAttribute( "M43" ), ValueElement->FloatAttribute( "M44" ) ) );
									}
									else if ( TypeName == "texture" )
									{
										AoTexture2D* Texture = dynamic_cast< AoTexture2D* >( AoAssetManager::GetInstance( ).LoadAsset(
											AoString::StringToWString( ValueElement->Attribute( "Path" ) ),
											AoString::StringToWString( ValueElement->Attribute( "Name" ) ),
											AoString::StringToWString( ValueElement->Attribute( "Ext" ) ) ) );

										bool bIsValidTexture = Texture != nullptr;
										if ( bIsValidTexture )
										{
											CreatedAsset->SetTextureByName(
												PropertyName,
												Texture );
										}
									}
								}

								CurrentProperty =
									CurrentProperty->NextSiblingElement( "Property" );
							}
						}
					}
				}
			}
		}
		break;
	}

	return CreatedAsset;
}

AoMaterial* AoAssetFactory::CreateMaterialWithShader( AoShader* Shader )
{
	return new AoMaterial( Shader );
}