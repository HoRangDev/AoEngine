#pragma once
#include <unordered_map>
#include <atomic>
#include <vector>

using string = std::wstring;

class AoApplication;
class AoAsset;
class AoAssetManager
{
private:
	AoAssetManager( );

public :
	~AoAssetManager( );

	static AoAssetManager& GetInstance( );
	void Initialize( );
	void DeInitialize( );
	static void ForceDeallocate( );

	void LoadAllAssets( );
	void UnloadAllAssets( );

	// Assets 폴더에서 상대적인 위치의 에셋을 로드해옴.
	AoAsset* LoadAsset( const string& FilePath, const string& FileName, const string& FileExt );
	void UnloadAsset( AoAsset* Target );

	bool IsValidAsset( AoAsset* Target );

	unsigned int GetLoadedAssetQuantity( ) const;

	string GetAssetDirectoryPath( ) const;

private:
	void SearchDirectory( const string& RootDirectoryName, const string& SubDirectory );

private:
	static AoAssetManager* Instance;
	std::unordered_map<string, AoAsset*> Database;
	std::atomic<unsigned int> LoadedAssetQuantity;

	std::vector<string> FoundFilesList;

	string AssetDirectoryPath;

};