#pragma once
#include "AoType.h"

class AoWindow;
class AoRenderer;
class AoAssetManager;
class AoProfiler;
class AoLevel;
class AoApplication
{
public:
	AoApplication( string Name, uint32_t Width, uint32_t Height );
	AoApplication( const AoApplication& ) = delete;
	~AoApplication( );

	int Excute( );

	static AoRenderer& GetRenderer( );
	static bool IsInitialized( );

	static uint32 GetFPS( );

private:
	void Initialize( );
	void DeInitialize( );

private:
	static bool bIsInitialized;
	AoWindow* Window;
	static AoRenderer* Renderer;
	AoLevel* LoadedLevel;

	static uint32 FPSCount;

};
