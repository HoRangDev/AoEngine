#include "AoTestActor.h"

AoTestActor::AoTestActor( string Name ) : AoActor( Name )
{
}

void AoTestActor::Tick( float DeltaTime )
{
	Angle += RotateSpeed * DeltaTime;
	Transform->SetRotationY( Angle );

	if( Angle >= 360.0f )
	{
		Angle = 0.0f;
	}
}
