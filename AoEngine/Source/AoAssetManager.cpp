#include "WindowsInc.h"
#include <io.h>
#include <forward_list>
#include <string>
#include "AoAssetManager.h"
#include "AoAssetFactory.h"
#include "AoAsset.h"

AoAssetManager* AoAssetManager::Instance = nullptr;

AoAssetManager::AoAssetManager( )
	: LoadedAssetQuantity( 0 ),
	AssetDirectoryPath( TEXT( "" ) )
{
}

AoAssetManager::~AoAssetManager( )
{
}

AoAssetManager& AoAssetManager::GetInstance( )
{
	if( Instance == nullptr )
	{
		Instance = new AoAssetManager( );
	}

	return *Instance;
}

void AoAssetManager::Initialize( )
{
	wchar_t Buffer[ 255 ];
	GetCurrentDirectory( 255, Buffer );
	AssetDirectoryPath = Buffer;

	string ReplaceTarget = TEXT( "\\" );
	string Replace = TEXT( "/" );
	string::size_type Offset = 0;

	while( true )
	{
		Offset = AssetDirectoryPath.find( ReplaceTarget, Offset );
		if( string::npos == Offset )
		{
			break;
		}
		else
		{
			AssetDirectoryPath.replace( Offset, ReplaceTarget.length( ), Replace );
		}
	}

	AssetDirectoryPath += TEXT( "/Assets" );
	SearchDirectory( AssetDirectoryPath, TEXT("") );
	LoadAllAssets( );
}

void AoAssetManager::DeInitialize( )
{
	UnloadAllAssets( );
	delete Instance;
	Instance = nullptr;
}

void AoAssetManager::SearchDirectory( const string& RootDirectoryPath, const string& SubDirectoryName )
{
	std::forward_list<string> SubDirectoryList;
	string LoadTargetPath =  RootDirectoryPath + SubDirectoryName;

	SetCurrentDirectory( LoadTargetPath.c_str() );

	struct _wfinddata64i32_t FoundFile;
	intptr_t FileHandle = _wfindfirst( TEXT("*.*"), &FoundFile );
	if( FileHandle == -1 )
	{
		return;
	}

	do
	{
		if( FoundFile.attrib & _A_SUBDIR )
		{
			SubDirectoryList.push_front( FoundFile.name );
		}
		else
		{
			FoundFilesList.push_back( LoadTargetPath + TEXT( "/" ) + FoundFile.name );
		}
	} while ( _wfindnext( FileHandle, &FoundFile ) == 0 );
	_findclose( FileHandle );

	for( string SubDirName : SubDirectoryList )
	{
		if ( SubDirName != TEXT( ".." ) && SubDirName != TEXT( "." ))
		{
			SearchDirectory( LoadTargetPath + TEXT("/"), SubDirName );
		}
	}

	SetCurrentDirectory( RootDirectoryPath.c_str( ) );
}

void AoAssetManager::LoadAllAssets( )
{
	wchar_t Drive[ 5 ];
	wchar_t DirectoryName[ 200 ];
	wchar_t FileName[ 100 ];
	wchar_t FileExtension[ 10 ];

	for ( string FoundFilesFullPath : FoundFilesList )
	{
		ZeroMemory( Drive, sizeof( Drive ) );
		ZeroMemory( DirectoryName, sizeof( DirectoryName ) );
		ZeroMemory( FileName, sizeof( FileName ) );
		ZeroMemory( FileExtension, sizeof( FileExtension ) );

		_wsplitpath_s( FoundFilesFullPath.c_str( ), Drive, 5, DirectoryName, 200, FileName, 100, FileExtension, 10 );

		string FilePath = DirectoryName; 
		// Delete Root(Assets) Directory from Path
		string::size_type FilePathSubOffset = 
			FilePath.find( TEXT("Assets"), 0 ) +
			(sizeof( TEXT("Assets" ) ) / sizeof ( wchar_t )); 
		FilePath = FilePath.substr( FilePathSubOffset );
		_wcslwr_s( FileExtension, sizeof( FileExtension ) / sizeof( wchar_t ) );
		LoadAsset( FilePath, FileName, FileExtension );
	}
}

void AoAssetManager::UnloadAllAssets( )
{
	for ( auto Asset : Database )
	{
		delete Asset.second;
	}

	Database.clear( );
	FoundFilesList.clear( );
	LoadedAssetQuantity = 0;
}

AoAsset* AoAssetManager::LoadAsset( const string& FilePath, const string& FileName, const string& FileExt )
{
	string Key = FilePath + FileName + FileExt;
	auto Found = Database.find( Key );
	if ( Found == Database.end() )
	{
		++LoadedAssetQuantity;
		AoAsset* LoadedAsset = 
			AoAssetFactory::CreateAsset( AssetDirectoryPath, FilePath, FileName, FileExt );
		Database.insert( std::pair<string, AoAsset*>( Key, LoadedAsset ) );
		return ( LoadedAsset );
	}

	return ( ( *Found ).second );
}

void AoAssetManager::UnloadAsset( AoAsset* Target )
{
	string Key = Target->GetFilePath() + Target->GetFileName() + Target->GetFileExtension();
	auto Found = Database.find( Key );
	if ( Found != Database.end() )
	{
		Database.erase( Found );
		delete Target;
		--LoadedAssetQuantity;
	}
}

bool AoAssetManager::IsValidAsset( AoAsset* Target )
{
	for( auto Asset : Database )
	{
		if( Asset.second == Target )
		{
			return true;
		}
	}

	return false;
}

unsigned int AoAssetManager::GetLoadedAssetQuantity( ) const
{
	return LoadedAssetQuantity;
}

string AoAssetManager::GetAssetDirectoryPath( ) const
{
	return AssetDirectoryPath;
}