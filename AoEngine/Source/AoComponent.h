#pragma once
#include <vector>

class AoActor;
class AoComponent
{
public:
	using ComponentVector = std::vector<AoComponent*>;
	using ComponentVectorItr = ComponentVector::iterator;
	using ComponentVectorConstItr = ComponentVector::const_iterator;

	friend AoActor;

public:
	AoComponent( );
	virtual ~AoComponent( );

	virtual void SetActive( bool bIsActive );
	bool IsActive( ) const;

	AoActor* GetAttachedActor( ) const;

protected:
	virtual void OnAttach( ){ }
	virtual void OnDetach( ){ }

private:
	virtual void SetAttachedActor( AoActor* Actor );

protected:
	AoActor* Actor;
	bool bIsActive;

};