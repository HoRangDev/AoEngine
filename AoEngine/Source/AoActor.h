/**
* @details 액터는 Level 상에서 존재할수있는 모든 오브젝트 입니다.
		   만약 렌더링가능한 Component 를 가지고 있지않는 다면. 표시되지 않습니다.
		   (Parent Actor 는 Child Actor 를 업데이트해야하는 의무를 가집니다.)
* @author Yang Kyowon
* @data 2016-08-16
* @latestdata 2016-08-16
* @latestmodifier Yang Kyowon
*/

#pragma once
#include "AoType.h"
#include "AoTransform.h"
#include <vector>

class AoLevel;
class AoComponent;
class AoRenderComponent;
class AoActor
{
public:
	using ActorVector = std::vector<AoActor*>;
	using ActorVectorItr = ActorVector::iterator;
	using ActorVectorConstItr = ActorVector::const_iterator;

	using ComponentVector = std::vector<AoComponent*>;
	using ComponentVectorItr = ComponentVector::iterator;
	using ComponentVectorConstItr = ComponentVector::const_iterator;

public:
	AoActor( string Name );
	AoActor( );
	~AoActor( );

	void AttachChild( AoActor* const Child );
	void DetachChild( AoActor* const Child );
	AoActor* DetachChild( const string& Name );
	void DetachAllChild( bool bIsCleanup = true );

	void AttachComponent( AoComponent* const Component );
	void DetachComponent( AoComponent* const Component );
	void DetachAllComponent( bool bIsCleanup = true );

	static uint64 GetInstanceCount( );
	string GetName( ) const;

	AoActor* GetParent( ) const;
	AoLevel* GetRegisteredLevel( ) const;

	virtual void Tick( float DeltaTime )
	{
	}

	void SetActive( bool bIsActive );
	bool IsActive( ) const;
	bool IsRegisteredAtLevel( ) const;

	AoTransform* GetTransform( ) const;

	void MakeChildTransformDirty( );

private:
	friend AoLevel;
	virtual void Update( float DeltaTime ) final;

	void SetParent( AoActor* const Parent );
	void SetRegisteredLevel( AoLevel* const TargetLevel );

protected:
	bool bIsActive;
	bool bIsTick;

	AoRenderComponent* RenderComponent;
	AoTransform* Transform;

private:
	static atomic_uint64 InstanceCount;
	string Name;

	ActorVector Children;

	AoActor* Parent;
	AoLevel* RegisteredLevel;

	ComponentVector Components;

};