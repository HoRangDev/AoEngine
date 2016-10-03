#pragma once

#include <d3d11.h>
#include <D3DX11Effect.h>
#include <DirectXMath.h>

#define ReleaseCOM(x) { if(x != nullptr){ x->Release(); x = nullptr; } }