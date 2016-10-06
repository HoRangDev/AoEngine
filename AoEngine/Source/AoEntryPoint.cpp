#include <crtdbg.h>
#include "WindowsInc.h"
#include "AoApplication.h"

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

int CALLBACK WinMain( HINSTANCE AppInstance, HINSTANCE PreviousInstance, LPSTR CmdLine, int CmdCount )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 389227 );
#endif

	AoApplication* Application = new AoApplication( TEXT( "AoEngine" ), 1280, 720 );
	int Return = Application->Excute( );
	delete Application;
	Application = nullptr;

	return 0;
}