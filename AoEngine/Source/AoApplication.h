#pragma once
#include <string>
using string = std::wstring;

class AoWindow;
class AoRenderer;
class AoLevel;
class AoApplication
{
public:
	AoApplication( string Name, uint32_t Width, uint32_t Height );
	AoApplication( const AoApplication& ) = delete;
	~AoApplication();

	int Excute();

	static AoRenderer* GetRenderer();

private:
	void Initialize();
	void DeInitialize();
	
private:
	AoWindow* Window;
	static AoRenderer* Renderer;
	AoLevel* LoadedLevel;

};
