#include "AoApplication.h"
#include "AoWindow.h"
#include "AoRenderer.h"
#include "AoLevel.h"
#include "AoAssetManager.h"
#include "AoInputLayouts.h"
#include "AoProfiler.h"
#include "AoTimeManager.h"
#include <assert.h>

bool AoApplication::bIsInitialized = false;
AoRenderer* AoApplication::Renderer = nullptr;
uint32 AoApplication::FPSCount = 0;

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
	using namespace std::chrono;

	Initialize( );

	AoProfiler& Profiler = AoProfiler::GetInstance( );
	AoTimeManager& TimeManager = AoTimeManager::GetInstance( );
	double RawDeltaTime = 0.0;
	
	float FPSElasedTime = 0.0f;
	uint32 FrameCount = 0;

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

		AoProfileSample MainLoopProfileSample( high_resolution_clock::now( ) );
		/** Main Loop		*/

		AoProfileSample UpdateLoopProfileSample( high_resolution_clock::now( ) );
		// Update
		if ( LoadedLevel != nullptr )
		{
			/* Scale */
			LoadedLevel->Update( RawDeltaTime );
		}
		UpdateLoopProfileSample.SetProfileEndPoint( high_resolution_clock::now( ) );
		Profiler.RegisterSample( TEXT( "LogicUpdate" ), UpdateLoopProfileSample );

		AoProfileSample RenderLoopProfileSample( high_resolution_clock::now( ) );
		// Render
		Renderer->BeginFrame( );
		Renderer->Render( );
		Renderer->EndFrame( );
		RenderLoopProfileSample.SetProfileEndPoint( high_resolution_clock::now( ) );
		Profiler.RegisterSample( TEXT( "Rendering" ), RenderLoopProfileSample );

		// Increase FPS Count
		++FrameCount;

		/** Main Loop End	*/
		MainLoopProfileSample.SetProfileEndPoint( high_resolution_clock::now( ) );
		Profiler.RegisterSample( TEXT( "MainLoop" ), MainLoopProfileSample );

		RawDeltaTime = MainLoopProfileSample.GetDeltaTime( );
		TimeManager.Tick( RawDeltaTime );

		FPSElasedTime += RawDeltaTime;
		if( FPSElasedTime >= 1.0f )
		{
			FPSCount = FrameCount;
			FrameCount = 0;
			FPSElasedTime = 0.0f;
		}
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

uint32 AoApplication::GetFPS( )
{
	return FPSCount;
}

void AoApplication::Initialize( )
{
	//@TODO: Load App Initialize Informations from Config.
	Renderer = new AoRenderer( *Window );

	AoAssetManager::GetInstance( ).Initialize( );
	AoProfiler::GetInstance( ).Initialize( );
	AoInputLayouts::Initialize( );

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

	AoInputLayouts::DeInitialize( );
	AoProfiler::ForceDeallocate( );
	AoAssetManager::ForceDeallocate( );
}