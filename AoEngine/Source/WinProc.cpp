#include "WinProc.h"
#include "AoApplication.h"
#include "AoRenderer.h"

LRESULT CALLBACK WinProc( HWND Handle, UINT Msg, WPARAM WParam, LPARAM LParam )
{
	switch ( Msg )
	{
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage( 0 );
		return 0;

	case WM_SIZE:
		if ( AoApplication::IsInitialized( ) )
		{
			AoRenderer& Renderer = AoApplication::GetRenderer( );
			Renderer.ResizeBackBuffer( );
		}
		break;
	}

	return DefWindowProc( Handle, Msg, WParam, LParam );
}