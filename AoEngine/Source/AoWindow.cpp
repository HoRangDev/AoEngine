#include "AoWindow.h"
#include "WinProc.h"

uint32_t AoWindow::DefaultWidth = 800;
uint32_t AoWindow::DefaultHeight = 600;

AoWindow::AoWindow( string Name, uint32_t Width, uint32_t Height ) :
	Name( Name ),
	Width( Width ),
	Height( Height )
{
	// Define windows style
	WNDCLASS WC = { 0 };
	WC.style = CS_OWNDC;
	WC.lpfnWndProc = WinProc;
	//@TODO: Replace DX Cursor Later
	WC.hCursor = LoadCursor( nullptr, IDC_ARROW );
	WC.lpszClassName = Name.c_str( );
	RegisterClass( &WC );

	Handle = CreateWindow( Name.c_str( ), Name.c_str( ),
						   WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
						   0, 0, Width, Height,
						   nullptr, nullptr, nullptr, nullptr );
}

AoWindow::AoWindow( ) :
	AoWindow( TEXT( "AoEngine" ), DefaultWidth, DefaultHeight )
{

}

uint32_t AoWindow::GetWidth( ) const
{
	return Width;
}

uint32_t AoWindow::GetHeight( ) const
{
	return Height;
}

HWND AoWindow::GetHandle( ) const
{
	return Handle;
}
