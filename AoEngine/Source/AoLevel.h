#pragma once
#include <list>
#include <string>
using string = std::wstring;

class AoActor;
class AoLevel
{
public:
	using ActorList = std::list<AoActor*>;
	using ActorListItr = ActorList::iterator;
	using ActorListConstItr = ActorList::const_iterator;

public:
	AoLevel( );
	virtual ~AoLevel( );

	void RegisterActor( AoActor* const Actor );
	void UnRegisterActor( AoActor* const Actor );
	AoActor* UnRegisterActor( const string& Name );
	void UnRegisterAllActor( bool bIsCleanup );

	void Update( float DeltaTime );

private:
	ActorList RegisteredActors;

};