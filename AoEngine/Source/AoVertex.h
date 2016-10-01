#pragma once
#include "AoVector2.h"
#include "AoVector.h"
#include "AoVector4.h"

namespace AoVertex
{
	enum class EAoVertex
	{
		Basic32			// Position, Normal, Tex1UV
	};

	struct AoBasic32
	{
		AoVector	Position;
		AoVector	Normal;
		AoVector2	Tex1UV;
	};
}