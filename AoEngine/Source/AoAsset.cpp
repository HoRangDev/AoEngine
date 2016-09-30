#include "AoAsset.h"
#include "AoAssetManager.h"
#include "WindowsInc.h"

const SAssetTypeMatchInfo AoAsset::MatchInfo[ ] =
{
	{ TEXT( ".fx" ), EAssetType::Shader },
	{ TEXT( ".hlsl" ), EAssetType::Shader },
	{ TEXT( ".txt" ), EAssetType::Text },
	{ TEXT( ".png" ), EAssetType::Texture2D},
	{ TEXT( ".jpg" ), EAssetType::Texture2D },
	{ TEXT( ".fbx" ), EAssetType::Mesh },
	{ TEXT( ".mp3" ), EAssetType::Audio },
	{ TEXT( ".wav" ), EAssetType::Audio },
	{ TEXT( ".ogg" ), EAssetType::Audio },
	{ TEXT( ".cfg"), EAssetType::Config }
};

AoAsset::AoAsset( )
	: FileName( TEXT( "" ) ), FilePath( TEXT( "" ) ), FileExtension( TEXT( "" ) ),
	Type( EAssetType::Unknown )
{
}

AoAsset::~AoAsset( )
{
}

void AoAsset::SetFileName( const string& FileName )
{
	this->FileName = FileName;
}

string AoAsset::GetFileName( ) const
{
	return FileName;
}

void AoAsset::SetFilePath( const string& FilePath )
{
	this->FilePath = FilePath;
}

string AoAsset::GetFilePath( ) const
{
	return FilePath;
}

string AoAsset::GetFileFullPath( ) const
{
	return AoAssetManager::GetInstance()->GetAssetDirectoryPath() + FilePath;
}

void AoAsset::SetFileExtension( const string& FileExtension )
{
	this->FileExtension = FileExtension;
	int NumOfMatchInfo = sizeof( MatchInfo ) / sizeof( SAssetTypeMatchInfo );
	for ( int Index = 0; Index < NumOfMatchInfo; ++Index )
	{
		if( MatchInfo[ Index ].Extension == FileExtension )
		{
			Type = MatchInfo[ Index ].MatchType;
		}
	}
}

string AoAsset::GetFileExtension( ) const
{
	return FileExtension;
}

EAssetType AoAsset::GetType( ) const
{
	return Type;
}