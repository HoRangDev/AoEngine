#pragma once
#include "AoActor.h"

class AoTestActor : public AoActor
{
public:
	AoTestActor( string Name );

	virtual void Tick( float DeltaTime ) override;

private:
	float Angle = 0.0f;
	float RotateSpeed = 90.0f;

};