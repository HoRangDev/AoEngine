#pragma once
#include <string>
using string = std::wstring;

enum class EAssetType
{
	Unknown,
	Texture2D,
	Shader,
	Mesh,
	Audio,
	Text,
	Config
};

struct SAssetTypeMatchInfo
{
	string		Extension;
	EAssetType	MatchType;
};

class AoAsset
{
protected:
	AoAsset( );

public:
	virtual ~AoAsset( );

	void SetFileName( const string& FileName );
	string GetFileName( ) const;
	void SetFilePath( const string& FileFullPath );
	string GetFilePath( ) const;
	string GetFileFullPath( ) const;
	void SetFileExtension( const string& FileExtension );
	string GetFileExtension( ) const;
	EAssetType GetType( ) const;

private:
	string		FileName;
	string		FilePath;
	string		FileExtension;
	EAssetType	Type;

public:
	static const SAssetTypeMatchInfo MatchInfo[ ];

};