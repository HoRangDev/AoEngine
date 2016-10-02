#include <assert.h>
#include "AoApplication.h"
#include "AoWindow.h"
#include "AoRenderer.h"
#include "AoLevel.h"
#include "AoAssetManager.h"

bool AoApplication::bIsInitialized = false;
AoRenderer* AoApplication::Renderer = nullptr;

AoApplication::AoApplication( string Name, uint32_t Width, uint32_t Height ) :
	Window( new AoWindow( Name, Width, Height ) ),
	LoadedLevel( nullptr )
{
}

AoApplication::~AoApplication( )
{

}

int AoApplication::Excute( )
{
	Initialize( );

	MSG Msg = { 0 };
	while ( true )
	{
		if ( PeekMessage( &Msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &Msg );
			DispatchMessage( &Msg );

			if ( Msg.message == WM_QUIT )
			{
				break;
			}
		}

		/** Main Loop		*/
		// Update
		if ( LoadedLevel != nullptr )
		{
			//LoadedLevel->Update()
		}
		// Render
		Renderer->BeginFrame( );
		Renderer->Render( );
		Renderer->EndFrame( );
		/** Main Loop End	*/
	}

	DeInitialize( );
	return 0;
}

AoRenderer& AoApplication::GetRenderer( )
{
	assert( Renderer != nullptr );
	return ( *Renderer );
}

bool AoApplication::IsInitialized( )
{
	return bIsInitialized;
}

void AoApplication::Initialize( )
{
	//@TODO: Load App Initialize Informations from Config.
	Renderer = new AoRenderer( *Window );
	AoAssetManager::GetInstance( ).Initialize( );

	bIsInitialized = true;
}

void AoApplication::DeInitialize( )
{
	if ( LoadedLevel != nullptr )
	{
		delete LoadedLevel;
		LoadedLevel = nullptr;
	}

	if ( Renderer != nullptr )
	{
		delete Renderer;
		Renderer = nullptr;
	}

	if ( Window != nullptr )
	{
		delete Window;
		Window = nullptr;
	}

	AoAssetManager::GetInstance( ).DeInitialize( );
}