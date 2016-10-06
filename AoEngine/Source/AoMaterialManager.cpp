#include "AoMaterialManager.h"
#include "AoMaterial.h"

AoMaterialManager* AoMaterialManager::Instance = nullptr;

AoMaterialManager::AoMaterialManager( )
{
}

AoMaterialManager::~AoMaterialManager( )
{
}

AoMaterialManager& AoMaterialManager::GetInstance( )
{
	if ( Instance == nullptr )
	{
		Instance = new AoMaterialManager( );
	}

	return *Instance;
}

void AoMaterialManager::Initialize( )
{

}

void AoMaterialManager::DeInitialize( )
{
	/* Material Manager dont have any responsibility */
	MaterialList.clear( );
}

void AoMaterialManager::ForceDeallocate( )
{
	if ( Instance != nullptr )
	{
		delete Instance;
		Instance = nullptr;
	}
}

void AoMaterialManager::RegisterMaterial( AoMaterial* Material )

{
	if ( Material != nullptr )
	{
		AoMaterial* FoundMaterial = GetMaterial( Material->GetMaterialName( ) );
		if ( FoundMaterial == nullptr )
		{
			MaterialList.push_back( Material );
		}
	}
}

bool AoMaterialManager::UnRegisterMaterial( AoMaterial* Material )
{
	return UnRegisterMaterial( Material->GetMaterialName( ) );
}

bool AoMaterialManager::UnRegisterMaterial( const string& Name )
{
	for ( auto Itr = MaterialList.begin(); Itr != MaterialList.end(); )
	{
		if ( ( *Itr )->GetMaterialName( ) == Name )
		{
			Itr = MaterialList.erase( Itr );
			return true;
		}
		else
		{
			++Itr;
		}
	}

	return false;
}

void AoMaterialManager::UnRegisterAllMaterial( )
{
	MaterialList.clear( );
}

AoMaterial* AoMaterialManager::GetMaterial( const string& Name ) const
{
	for( auto Material : MaterialList )
	{
		if( Material->GetMaterialName() == Name )
		{
			return Material;
		}
	}

	return nullptr;
}

void AoMaterialManager::BatchMatrixSet( const string& PropertyName, const AoMatrix4x4& Value )
{
	for ( auto Material : MaterialList )
	{
		Material->SetMatrixByName( PropertyName, Value );
	}
}