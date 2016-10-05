#include "WindowsInc.h"
#include "AoApplication.h"

int CALLBACK WinMain( HINSTANCE AppInstance, HINSTANCE PreviousInstance, LPSTR CmdLine, int CmdCount )
{
	AoApplication* Application = new AoApplication( TEXT( "AoEngine" ), 800, 600 );
	int Return = Application->Excute( );
	delete Application;
	Application = nullptr;

	return Return;
}