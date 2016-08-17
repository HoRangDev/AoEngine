#include "AoApplication.h"
#include "AoWindow.h"
#include "AoDX11Renderer.h"
#include "AoLevel.h"

AoRenderer* AoApplication::Renderer = nullptr;

AoApplication::AoApplication( string Name, uint32_t Width, uint32_t Height ) :
	Window(new AoWindow(Name, Width, Height)),
	LoadedLevel(nullptr)
{
	Renderer = new AoDX11Renderer( *Window );
}

AoApplication::~AoApplication()
{

}

int AoApplication::Excute()
{
	Initialize();

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
		if( LoadedLevel != nullptr )
		{
			//LoadedLevel->Update()
		}
		// Render
		Renderer->BeginFrame();
		Renderer->Render();
		Renderer->EndFrame();
		/** Main Loop End	*/
	}

	DeInitialize();
	return 0;
}

AoRenderer* AoApplication::GetRenderer()
{
	return Renderer;
}

void AoApplication::Initialize()
{
	//@TODO: Load App Initialize Informations from Config.
}

void AoApplication::DeInitialize()
{
	if( LoadedLevel != nullptr )
	{
		delete LoadedLevel;
		LoadedLevel = nullptr;
	}

	if( Renderer != nullptr )
	{
		delete Renderer;
		Renderer = nullptr;
	}

	if( Window != nullptr )
	{
		delete Window;
		Window = nullptr;
	}
}
