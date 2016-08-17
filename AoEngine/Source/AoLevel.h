#pragma once
#include "AoActor.h"

class AoLevel
{
public:
	AoLevel();
	~AoLevel();

	void RegisterActor( AoActor* const Actor );
	void UnRegisterActor( AoActor* const Actor );
	AoActor* UnRegisterActor( const string& Name );
	void UnRegisterAllActor( bool bIsCleanup );

	void Update( float DeltaTime );

private:
	AoActor::ActorVector RegisteredActors;

};