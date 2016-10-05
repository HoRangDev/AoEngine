#include "AoMaterial.h"
#include "AoMaterialProperty.h"
#include "AoMaterialIntProperty.h"
#include "AoMaterialFloatProperty.h"
#include "AoMaterialBoolProperty.h"
#include "AoMaterialMatrixProperty.h"
#include "AoMaterialVectorProperty.h"
#include "AoMaterialTextureProperty.h"
#include "AoShader.h"
#include "AoStringUtility.h"
#include "AoMatrix4x4.h"
#include "AoTexture2D.h"
#include <tinyxml2.h>

AoMaterial::AoMaterial( AoShader* Shader )
	: Shader( Shader )
{
}

AoMaterial::~AoMaterial( )
{
	DeleteAllProperties( );
}

ID3DX11EffectTechnique * AoMaterial::GetTechniqueByName( const string& PropertyName ) const
{
	return Shader->GetTechniqueByName( PropertyName );
}

AoMaterialProperty* AoMaterial::GetPropertyByName( const string & PropertyName ) const
{
	auto Itr = Properties.find( PropertyName );
	if ( Itr != Properties.end( ) )
	{
		return ( *Itr ).second;
	}

	return nullptr;
}

int AoMaterial::GetIntByName( const string& PropertyName ) const
{
	AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
	if( FoundProperty != nullptr )
	{
		AoMaterialIntProperty* Property =
			dynamic_cast< AoMaterialIntProperty* >( FoundProperty );

		if ( Property != nullptr )
		{
			return Property->GetData( );
		}
	}

	return 0;
}

float AoMaterial::GetFloatByName( const string& PropertyName ) const
{
	AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
	if ( FoundProperty != nullptr )
	{
		AoMaterialFloatProperty* Property =
			dynamic_cast< AoMaterialFloatProperty* >( FoundProperty );

		if ( Property != nullptr )
		{
			return Property->GetData( );
		}
	}

	return 0.0f;
}

bool AoMaterial::GetBoolByName( const string& PropertyName ) const
{
	AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
	if ( FoundProperty != nullptr )
	{
		AoMaterialBoolProperty* Property =
			dynamic_cast< AoMaterialBoolProperty* >( FoundProperty );

		if ( Property != nullptr )
		{
			return Property->GetData( );
		}
	}

	return false;
}

AoTexture2D* AoMaterial::GetTextureByName( const string& PropertyName ) const
{
	AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
	if ( FoundProperty != nullptr )
	{
		AoMaterialTextureProperty* Property =
			dynamic_cast< AoMaterialTextureProperty* >( FoundProperty );

		if ( Property != nullptr )
		{
			return Property->GetData( );
		}
	}

	return nullptr;
}

AoMatrix4x4 AoMaterial::GetMatrixByName( const string& PropertyName ) const
{
	AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
	if ( FoundProperty != nullptr )
	{
		AoMaterialMatrixProperty* Property =
			dynamic_cast< AoMaterialMatrixProperty* >( FoundProperty );

		if ( Property != nullptr )
		{
			return Property->GetData( );
		}
	}

	return AoMatrix4x4::Identity;
}

AoVector4 AoMaterial::GetVectorByName( const string& PropertyName ) const
{
	AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
	if ( FoundProperty != nullptr )
	{
		AoMaterialVectorProperty* Property =
			dynamic_cast< AoMaterialVectorProperty* >( FoundProperty );

		if ( Property != nullptr )
		{
			return Property->GetData( );
		}
	}

	return AoVector4::Zero;
}

void AoMaterial::SetIntByName( const string& PropertyName, int Value )
{
	if( Shader->IsValidProperty( PropertyName ) )
	{
		AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
		if( FoundProperty != nullptr )
		{
			AoMaterialIntProperty* Property = 
				dynamic_cast< AoMaterialIntProperty* >( FoundProperty );

			if ( Property != nullptr )
			{
				Property->SetData( Value );
			}
		}
		else
		{
			AoMaterialIntProperty* NewProperty = 
				new AoMaterialIntProperty( Value, PropertyName );

			Properties.insert( std::pair<string, AoMaterialProperty*>( PropertyName, NewProperty ) );
		}
	}
}

void AoMaterial::SetFloatByName( const string& PropertyName, float Value )
{
	if ( Shader->IsValidProperty( PropertyName ) )
	{
		AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
		if ( FoundProperty != nullptr )
		{
			AoMaterialFloatProperty* Property =
				dynamic_cast< AoMaterialFloatProperty* >( FoundProperty );

			if ( Property != nullptr )
			{
				Property->SetData( Value );
			}
		}
		else
		{
			AoMaterialFloatProperty* NewProperty =
				new AoMaterialFloatProperty( Value, PropertyName );

			Properties.insert( std::pair<string, AoMaterialProperty*>( PropertyName, NewProperty ) );
		}
	}
}

void AoMaterial::SetBoolByName( const string& PropertyName, bool Value )
{
	if ( Shader->IsValidProperty( PropertyName ) )
	{
		AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
		if ( FoundProperty != nullptr )
		{
			AoMaterialBoolProperty* Property =
				dynamic_cast< AoMaterialBoolProperty* >( FoundProperty );

			if ( Property != nullptr )
			{
				Property->SetData( Value );
			}
		}
		else
		{
			AoMaterialBoolProperty* NewProperty =
				new AoMaterialBoolProperty( Value, PropertyName );

			Properties.insert( std::pair<string, AoMaterialProperty*>( PropertyName, NewProperty ) );
		}
	}
}

void AoMaterial::SetTextureByName( const string& PropertyName, AoTexture2D* Value )
{
	if ( Shader->IsValidProperty( PropertyName ) )
	{
		AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
		if ( FoundProperty != nullptr )
		{
			AoMaterialTextureProperty* Property =
				dynamic_cast< AoMaterialTextureProperty* >( FoundProperty );

			if ( Property != nullptr )
			{
				Property->SetData( Value );
			}
		}
		else
		{
			AoMaterialTextureProperty* NewProperty =
				new AoMaterialTextureProperty( Value, PropertyName );

			Properties.insert( std::pair<string, AoMaterialProperty*>( PropertyName, NewProperty ) );
		}
	}
}

void AoMaterial::SetMatrixByName( const string& PropertyName, const AoMatrix4x4& Value )
{
	if ( Shader->IsValidProperty( PropertyName ) )
	{
		AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
		if ( FoundProperty != nullptr )
		{
			AoMaterialMatrixProperty* Property =
				dynamic_cast< AoMaterialMatrixProperty* >( FoundProperty );

			if ( Property != nullptr )
			{
				Property->SetData( Value );
			}
		}
		else
		{
			AoMaterialMatrixProperty* NewProperty =
				new AoMaterialMatrixProperty( Value, PropertyName );

			Properties.insert( std::pair<string, AoMaterialProperty*>( PropertyName, NewProperty ) );
		}
	}
}

void AoMaterial::SetVectorByName( const string& PropertyName, const AoVector4& Value )
{
	if ( Shader->IsValidProperty( PropertyName ) )
	{
		AoMaterialProperty* FoundProperty = GetPropertyByName( PropertyName );
		if ( FoundProperty != nullptr )
		{
			AoMaterialVectorProperty* Property =
				dynamic_cast< AoMaterialVectorProperty* >( FoundProperty );

			if ( Property != nullptr )
			{
				Property->SetData( Value );
			}
		}
		else
		{
			AoMaterialVectorProperty* NewProperty =
				new AoMaterialVectorProperty( Value, PropertyName );

			Properties.insert( std::pair<string, AoMaterialProperty*>( PropertyName, NewProperty ) );
		}
	}
}

void AoMaterial::SetMaterialName( const string& Name )
{
	this->MaterialName = Name;
}

string AoMaterial::GetMaterialName( ) const
{
	return MaterialName;
}

void AoMaterial::SetShader( AoShader* Shader )
{
	if ( this->Shader != Shader )
	{
		this->Shader = Shader;
		DeleteAllProperties( );
	}
}

AoShader* AoMaterial::GetShader( ) const
{
	return Shader;
}

void AoMaterial::ApplyPropertiesToShader( )
{
	for( auto PropertyPair : Properties )
	{
		AoMaterialProperty* Property = PropertyPair.second;
		if( Property != nullptr )
		{
			Property->ApplyToGlobalVariable( Shader );
		}
	}
}

void AoMaterial::SaveToFile( const string& FileName, const AoMaterial* Material )
{
	bool bIsValidMaterial = Material != nullptr;
	if ( bIsValidMaterial )
	{
		tinyxml2::XMLDocument Document;
		auto RootNode = Document.NewElement( "Material" );
		Document.InsertFirstChild( RootNode );

		auto MaterialNameNode = Document.NewElement( "MaterialName" );
		MaterialNameNode->SetText( AoStringUtility::WStringToString( Material->GetMaterialName( ) ).c_str( ) );
		RootNode->InsertEndChild( MaterialNameNode );

		AoShader* Shader = Material->GetShader( );
		auto UseShaderAssetNode = Document.NewElement( "UseShaderAsset" );
		UseShaderAssetNode->SetAttribute( "Path", AoStringUtility::WStringToString( Shader->GetFilePath( ) ).c_str( ) );
		UseShaderAssetNode->SetAttribute( "Name", AoStringUtility::WStringToString( Shader->GetFileName( ) ).c_str( ) );
		UseShaderAssetNode->SetAttribute( "Ext", AoStringUtility::WStringToString( Shader->GetFileExtension( ) ).c_str( ) );
		RootNode->InsertEndChild( UseShaderAssetNode );

		auto PropertiesNode = Document.NewElement( "Properties" );
		for ( auto PropertyPair : Material->Properties )
		{
			AoMaterialProperty* Property = PropertyPair.second;
			if ( Property != nullptr )
			{
				auto PropertyNode = Document.NewElement( "Property" );
				auto ValueNode = Document.NewElement( "Value" );
				if ( typeid( *Property ) == typeid( AoMaterialIntProperty ) )
				{
					AoMaterialIntProperty* IntProperty = reinterpret_cast< AoMaterialIntProperty* >( Property );
					PropertyNode->SetAttribute( "Type", "int" );
					PropertyNode->SetAttribute( "Name", AoStringUtility::WStringToString( Property->GetName( ) ).c_str( ) );
					ValueNode->SetAttribute( "Scalar", IntProperty->GetData( ) );
				}
				else if ( typeid( *Property ) == typeid( AoMaterialFloatProperty ) )
				{
					AoMaterialFloatProperty* FloatProperty = reinterpret_cast< AoMaterialFloatProperty* >( Property );
					PropertyNode->SetAttribute( "Type", "float" );
					PropertyNode->SetAttribute( "Name", AoStringUtility::WStringToString( Property->GetName( ) ).c_str( ) );
					ValueNode->SetAttribute( "Scalar", FloatProperty->GetData( ) );
				}
				else if ( typeid( *Property ) == typeid( AoMaterialBoolProperty ) )
				{
					AoMaterialBoolProperty* BoolProperty = reinterpret_cast< AoMaterialBoolProperty* >( Property );
					PropertyNode->SetAttribute( "Type", "bool" );
					PropertyNode->SetAttribute( "Name", AoStringUtility::WStringToString( Property->GetName( ) ).c_str( ) );
					ValueNode->SetAttribute( "Scalar", BoolProperty->GetData( ) );
				}
				else if ( typeid( *Property ) == typeid( AoMaterialVectorProperty ) )
				{
					AoMaterialVectorProperty* VectorProperty = reinterpret_cast< AoMaterialVectorProperty* >( Property );
					PropertyNode->SetAttribute( "Type", "vector" );
					PropertyNode->SetAttribute( "Name", AoStringUtility::WStringToString( Property->GetName( ) ).c_str( ) );

					AoVector4 Vector = VectorProperty->GetData( );
					ValueNode->SetAttribute( "X", Vector.X );
					ValueNode->SetAttribute( "Y", Vector.Y );
					ValueNode->SetAttribute( "Z", Vector.Z );
					ValueNode->SetAttribute( "W", Vector.W );
				}
				else if ( typeid( *Property ) == typeid( AoMaterialMatrixProperty ) )
				{
					AoMaterialMatrixProperty* MatrixProperty = reinterpret_cast< AoMaterialMatrixProperty* >( Property );
					PropertyNode->SetAttribute( "Type", "matrix" );
					PropertyNode->SetAttribute( "Name", AoStringUtility::WStringToString( Property->GetName( ) ).c_str( ) );

					AoMatrix4x4 Matrix = MatrixProperty->GetData( );
					ValueNode->SetAttribute( "M11", Matrix.M[ 0 ][ 0 ] ); ValueNode->SetAttribute( "M12", Matrix.M[ 0 ][ 1 ] );
					ValueNode->SetAttribute( "M13", Matrix.M[ 0 ][ 2 ] ); ValueNode->SetAttribute( "M14", Matrix.M[ 0 ][ 3 ] );

					ValueNode->SetAttribute( "M21", Matrix.M[ 1 ][ 0 ] ); ValueNode->SetAttribute( "M22", Matrix.M[ 1 ][ 1 ] );
					ValueNode->SetAttribute( "M23", Matrix.M[ 1 ][ 2 ] ); ValueNode->SetAttribute( "M24", Matrix.M[ 1 ][ 3 ] );

					ValueNode->SetAttribute( "M31", Matrix.M[ 2 ][ 0 ] ); ValueNode->SetAttribute( "M32", Matrix.M[ 2 ][ 1 ] );
					ValueNode->SetAttribute( "M33", Matrix.M[ 2 ][ 2 ] ); ValueNode->SetAttribute( "M34", Matrix.M[ 2 ][ 3 ] );

					ValueNode->SetAttribute( "M41", Matrix.M[ 3 ][ 0 ] ); ValueNode->SetAttribute( "M42", Matrix.M[ 3 ][ 1 ] );
					ValueNode->SetAttribute( "M43", Matrix.M[ 3 ][ 2 ] ); ValueNode->SetAttribute( "M44", Matrix.M[ 3 ][ 3 ] );
				}
				else if ( typeid( *Property ) == typeid( AoMaterialTextureProperty ) )
				{
					AoMaterialTextureProperty* TextureProperty = reinterpret_cast< AoMaterialTextureProperty* >( Property );
					PropertyNode->SetAttribute( "Type", "matrix" );
					PropertyNode->SetAttribute( "Name", AoStringUtility::WStringToString( Property->GetName( ) ).c_str( ) );

					AoTexture2D* Texture = TextureProperty->GetData( );
					ValueNode->SetAttribute( "Path", AoStringUtility::WStringToString( Texture->GetFilePath( ) ).c_str( ) );
					ValueNode->SetAttribute( "Name", AoStringUtility::WStringToString( Texture->GetFileName( ) ).c_str( ) );
					ValueNode->SetAttribute( "Ext", AoStringUtility::WStringToString( Texture->GetFileExtension( ) ).c_str( ) );
				}

				PropertyNode->InsertEndChild( ValueNode );
				PropertiesNode->InsertEndChild( PropertyNode );
			}
		}

		RootNode->InsertEndChild( PropertiesNode );

		auto Error = Document.SaveFile( AoStringUtility::WStringToString( FileName ).c_str( ) );
	}
}

void AoMaterial::DeleteAllProperties( )
{
	for ( auto Property : Properties )
	{
		delete Property.second;
	}

	Properties.clear( );
}
