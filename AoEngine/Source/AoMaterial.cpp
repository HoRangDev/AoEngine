#include "AoMaterial.h"
#include "AoMaterialProperty.h"
#include "AoMaterialIntProperty.h"
#include "AoMaterialFloatProperty.h"
#include "AoMaterialBoolProperty.h"
#include "AoMaterialMatrixProperty.h"
#include "AoMaterialVectorProperty.h"
#include "AoMaterialTextureProperty.h"
#include "AoShader.h"
#include "AoMatrix4x4.h"

AoMaterial::AoMaterial( AoShader* Shader ) 
	: Shader( Shader )
{
}

AoMaterial::~AoMaterial( )
{
	for( auto Property : Properties )
	{
		delete Property.second;
	}

	Properties.clear( );
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