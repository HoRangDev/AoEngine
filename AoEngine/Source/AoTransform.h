#pragma once
#include "AoComponent.h"
#include "AoVector.h"

class AoTransform : public AoComponent
{
public:
	AoTransform( );
	~AoTransform( );

private:
	AoVector Position;
	AoVector Scale;
	AoVector Rotation;

};