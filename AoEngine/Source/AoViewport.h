#pragma once

struct AoViewport
{
public:
	AoViewport( float Width, float Height, float TopLeftX = 0.0f, float TopLeftY = 0.0f, float MinDepth = 0.0f, float MaxDepth = 1.0f );
	AoViewport();

public:
	float Width;
	float Height;
	float TopLeftX;
	float TopLeftY;
	float MinDepth;
	float MaxDepth;
};