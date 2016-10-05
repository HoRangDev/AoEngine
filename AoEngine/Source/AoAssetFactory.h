#pragma once
#include "AoType.h"
#include "AoAsset.h"

class AoAssetManager;
class AoModel;
class AoTexture2D;
class AoShader;
class AoMaterial;
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
	static AoMaterial* CreateMaterialFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoMaterial* CreateMaterialWithShader( AoShader* Shader );
	static AoAudio* CreateAudioFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoText* CreateTextFromFile( const string& FileFullPath, ESupportAssetExtension Extension );
	static AoConfig* CreateConfigFromFile( const string& FileFullPath, ESupportAssetExtension Extension );

};
