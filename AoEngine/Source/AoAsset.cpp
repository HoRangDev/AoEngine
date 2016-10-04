#include "AoAsset.h"
#include "AoAssetManager.h"
#include "WindowsInc.h"

const SAssetTypeMatchInfo AoAsset::MatchInfos[ ] =
{
	{ TEXT( ".cfg" ),		ESupportAssetExtension::CFG,		 EAssetType::Config		},
	{ TEXT( ".fbx" ),		ESupportAssetExtension::FBX,		 EAssetType::Model		},
	{ TEXT( ".obj" ),		ESupportAssetExtension::OBJ,		 EAssetType::Model		},
	{ TEXT( ".png" ),		ESupportAssetExtension::PNG,		 EAssetType::Texture2D	},
	{ TEXT( ".jpg" ),		ESupportAssetExtension::JPG,		 EAssetType::Texture2D	},
	{ TEXT( ".dds" ),		ESupportAssetExtension::DDS,		 EAssetType::Texture2D	},
	{ TEXT( ".fxo" ),		ESupportAssetExtension::FXO,		 EAssetType::Shader		},
	{ TEXT( ".material" ),	ESupportAssetExtension::Material,	 EAssetType::Material	},
	{ TEXT( ".mp3" ),		ESupportAssetExtension::MP3,		 EAssetType::Audio		},
	{ TEXT( ".wav" ),		ESupportAssetExtension::WAV,		 EAssetType::Audio		},
	{ TEXT( ".ogg" ),		ESupportAssetExtension::OGG,		 EAssetType::Audio		},
	{ TEXT( ".txt" ),		ESupportAssetExtension::TXT,		 EAssetType::Text		}
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
	return AoAssetManager::GetInstance().GetAssetDirectoryPath() + TEXT("/") + FilePath + FileName + FileExtension;
}

void AoAsset::SetFileExtension( const string& FileExtension )
{
	this->FileExtension = FileExtension;
	this->Type = GetAssetTypeFromFileExtension( FileExtension );
}

string AoAsset::GetFileExtension( ) const
{
	return FileExtension;
}

EAssetType AoAsset::GetType( ) const
{
	return Type;
}

SAssetTypeMatchInfo AoAsset::GetMatchInfoFromFileExtension( const string & Extension )
{
	int NumOfMatchInfo = sizeof( MatchInfos ) / sizeof( SAssetTypeMatchInfo );
	for ( int Index = 0; Index < NumOfMatchInfo; ++Index )
	{
		if ( MatchInfos[ Index ].Extension == Extension )
		{
			return MatchInfos[ Index ];
		}
	}

	return SAssetTypeMatchInfo( );
}

EAssetType AoAsset::GetAssetTypeFromFileExtension( const string& Extension )
{
	int NumOfMatchInfo = sizeof( MatchInfos ) / sizeof( SAssetTypeMatchInfo );
	for ( int Index = 0; Index < NumOfMatchInfo; ++Index )
	{
		if ( MatchInfos[ Index ].Extension == Extension )
		{
			return MatchInfos[ Index ].MatchType;
		}
	}

	return EAssetType::Unknown;
}

ESupportAssetExtension AoAsset::GetSupportExtensionFromFileExtension( const string & Extension )
{
	int NumOfMatchInfo = sizeof( MatchInfos ) / sizeof( SAssetTypeMatchInfo );
	for ( int Index = 0; Index < NumOfMatchInfo; ++Index )
	{
		if ( MatchInfos[ Index ].Extension == Extension )
		{
			return MatchInfos[ Index ].ExtensionType;
		}
	}

	return ESupportAssetExtension::Unknown;
}