#pragma comment(lib, "assimp_D.lib")
#include "AoAssetFactory.h"
#include "AoAssetManager.h"
#include "AoStringUtility.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoShader.h"
#include "AoMaterial.h"
#include "AoModel.h"
#include "AoMesh.h"
#include "AoTexture2D.h"
#include "AoGenericVertex.h"
#include "WindowsInc.h"
#include <sstream>
#include <fstream>
#include <iostream>
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
	case ESupportAssetExtension::Ext3DS:
		Assimp::Importer Importer;
		const aiScene* Scene = Importer.ReadFile(
			AoStringUtility::WStringToString( FileFullPath ),
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_SplitLargeMeshes |
			aiProcess_ConvertToLeftHanded |
			aiProcess_SortByPType |
			aiProcess_PreTransformVertices );

		if ( Scene != nullptr )
		{
			std::vector<AoMesh*> Meshes( Scene->mNumMeshes );
			for ( unsigned int MeshIndex = 0; MeshIndex < Scene->mNumMeshes; ++MeshIndex )
			{
				const aiMesh* Mesh = Scene->mMeshes[ MeshIndex ];
				VertexVector Vertices( Mesh->mNumVertices );
				IndexVector Indices( 3 * Mesh->mNumFaces );
				bool bIsHasNormals = Mesh->HasNormals( );
				bool bIsHasTangentAndBiNormals = Mesh->HasTangentsAndBitangents( );
				bool bIsHasTextureUV = Mesh->HasTextureCoords( 0 );
				bool bIsHasColor = Mesh->HasVertexColors( 0 );

				AoVector	Normal;
				AoVector4	Color;
				AoVector2	TextureUV;
				AoVector	Tangent;
				AoVector	BiNormal;
				for ( unsigned int Index = 0; Index < Mesh->mNumVertices; ++Index )
				{
					Normal = AoVector::Zero;
					Color = AoVector4::One;
					TextureUV = AoVector2::Zero;
					Tangent = AoVector::Zero;
					BiNormal = AoVector::Zero;

					if ( bIsHasColor )
					{
						aiColor4D aiColor = Mesh->mColors[ 0 ][ Index ];
						Color.X = aiColor.r;
						Color.Y = aiColor.g;
						Color.Z = aiColor.b;
						Color.W = aiColor.a;
					}
					if ( bIsHasTextureUV )
					{
						aiVector3D UVW = Mesh->mTextureCoords[ 0 ][ Index ];
						TextureUV.X = UVW.x;
						TextureUV.Y = UVW.y;
					}
					if ( bIsHasNormals )
					{
						aiVector3D aiNormal = Mesh->mNormals[ Index ];
						Normal.X = aiNormal.x;
						Normal.Y = aiNormal.y;
						Normal.Z = aiNormal.z;
					}
					if ( bIsHasTangentAndBiNormals )
					{
						aiVector3D aiTangent = Mesh->mTangents[ Index ];
						aiVector3D aiBiNormal = Mesh->mBitangents[ Index ];
						Tangent.X = aiTangent.x;
						Tangent.Y = aiTangent.y;
						Tangent.Z = aiTangent.z;

						BiNormal.X = aiBiNormal.x;
						BiNormal.Y = aiBiNormal.y;
						BiNormal.Z = aiBiNormal.z;
					}

					aiVector3D Position = Mesh->mVertices[ Index ];
					Vertices[ Index ] = AoGenericVertex(
						AoVector( Position.x, Position.y, Position.z ),
						Normal,
						TextureUV,
						Tangent,
						BiNormal );
				}

				for ( unsigned int Index = 0; Index < Mesh->mNumFaces; ++Index )
				{
					Indices[ Index * 3 + 0 ] = ( Mesh->mFaces[ Index ].mIndices[ 0 ] );
					Indices[ Index * 3 + 1 ] = ( Mesh->mFaces[ Index ].mIndices[ 1 ] );
					Indices[ Index * 3 + 2 ] = ( Mesh->mFaces[ Index ].mIndices[ 2 ] );
				}

				std::cout << Mesh->mName.C_Str( ) << std::endl;
				AoMesh* MeshData = new AoMesh( AoStringUtility::StringToWString( Mesh->mName.C_Str( ) ) );
				MeshData->Initialize(
					std::move( Vertices ),
					std::move( Indices ) );
				Meshes[ MeshIndex ] = MeshData;
			}

			CreatedAsset = new AoModel( std::move( Meshes ) );
		}
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
		auto Error = Document.LoadFile( AoStringUtility::WStringToString( FileFullPath ).c_str( ) );
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
							AoStringUtility::StringToWString( UseShaderElement->Attribute( "Path" ) ),
							AoStringUtility::StringToWString( UseShaderElement->Attribute( "Name" ) ),
							AoStringUtility::StringToWString( UseShaderElement->Attribute( "Ext" ) )
							) );

					bool bIsValidShader = UseShader != nullptr;
					if ( bIsValidShader )
					{
						CreatedAsset = new AoMaterial( UseShader );
						CreatedAsset->SetMaterialName( AoStringUtility::StringToWString( MaterialNameElement->GetText( ) ) );

						tinyxml2::XMLNode* PropertiesNode = RootNode->FirstChildElement( "Properties" );
						bool bIsHaveProperties = PropertiesNode != nullptr;
						if ( bIsHaveProperties )
						{
							tinyxml2::XMLElement* CurrentProperty =
								PropertiesNode->FirstChildElement( "Property" );
							while ( CurrentProperty != nullptr )
							{
								std::string TypeName =
									AoStringUtility::StringToLower( CurrentProperty->Attribute( "Type" ) );
								string PropertyName =
									AoStringUtility::StringToWString( CurrentProperty->Attribute( "Name" ) );

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
											AoStringUtility::StringToWString( ValueElement->Attribute( "Path" ) ),
											AoStringUtility::StringToWString( ValueElement->Attribute( "Name" ) ),
											AoStringUtility::StringToWString( ValueElement->Attribute( "Ext" ) ) ) );

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