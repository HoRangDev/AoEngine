#pragma once
#include <string>
#include "AoAsset.h"

using string = std::wstring;

class AoAssetManager;
class AoModel;
class AoTexture2D;
class AoShader;
class AoAudio;
class AoText;
class AoConfig;
class AoAssetFactory
{
public:
	static AoAsset* CreateAsset( const string& RootDirectoryPath, const string& FilePath, const string& FileName, const string& FileExtension );
	static AoModel* CreateModelFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoTexture2D* CreateTexture2DFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoShader* CreateShaderFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoAudio* CreateAudioFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoText* CreateTextFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoConfig* CreateConfigFromFile( const string& FileFullPath, ESupportAssetExtension Extension );

};
