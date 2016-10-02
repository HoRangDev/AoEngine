#pragma once
#include <string>
using string = std::wstring;

enum class EAssetType
{
	Unknown,
	Config,
	Model,
	Texture2D,
	Shader,
	Audio,
	Text,
};

// 지원 파일 형식들
enum class ESupportAssetExtension
{
	Unknown,
	CFG,
	FBX, OBJ,
	PNG, JPG, DDS,
	HLSL, FX,
	MP3, WAV, OGG,
	TXT
};

struct SAssetTypeMatchInfo
{
	string						Extension;
	ESupportAssetExtension		ExtensionType;
	EAssetType					MatchType;
};

class AoAssetFactory;
class AoAsset
{
	friend AoAssetFactory;

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

public:
	static SAssetTypeMatchInfo GetMatchInfoFromFileExtension( const string& Extension );
	static EAssetType GetAssetTypeFromFileExtension( const string& Extension );
	static ESupportAssetExtension GetSupportExtensionFromFileExtension( const string& Extension );

private:
	string		FileName;
	string		FilePath;
	string		FileExtension;
	EAssetType	Type;

public:
	static const SAssetTypeMatchInfo MatchInfos[ ];

};