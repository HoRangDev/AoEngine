#pragma once
#include "AoType.h"
#include <vector>

class AoMaterial;
class AoMatrix4x4;
class AoMaterialManager
{
private:
	AoMaterialManager( );

public:
	~AoMaterialManager( );
	static AoMaterialManager& GetInstance( );

	void Initialize( );
	void DeInitialize( );

	static void ForceDeallocate( );

	void RegisterMaterial( AoMaterial* Material );
	bool UnRegisterMaterial( AoMaterial* Material );
	bool UnRegisterMaterial( const string& Name );
	void UnRegisterAllMaterial( );

	AoMaterial* GetMaterial( const string& Name ) const;

	void BatchLightSet( );
	void BatchMatrixSet( const string& PropertyName, const AoMatrix4x4& Value );

private:
	using MaterialListType = std::vector< AoMaterial* >;
	static AoMaterialManager* Instance;
	MaterialListType MaterialList;

};