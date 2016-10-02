#pragma once
#include <string>
#include "AoAsset.h"

using string = std::wstring;

class AoAssetManager;
class AoModelAsset;
class AoTexture2DAsset;
class AoShaderAsset;
class AoAudioAsset;
class AoTextAsset;
class AoConfigAsset;
class AoAssetFactory
{
public:
	static AoAsset* CreateAsset( const string& RootDirectoryPath, const string& FilePath, const string& FileName, const string& FileExtension );
	static AoModelAsset* CreateModelFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoTexture2DAsset* CreateTexture2DFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoShaderAsset* CreateShaderFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoAudioAsset* CreateAudioFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoTextAsset* CreateTextFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoConfigAsset* CreateConfigFromFile( const string& FileFullPath, ESupportAssetExtension Extension );

};
