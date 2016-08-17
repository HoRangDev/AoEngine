/**
* @details ���ʹ� Level �󿡼� ǥ�õɼ��ִ� ��� ������Ʈ �Դϴ�.
		   ���� ������������ Component �� ������ �����ʴ� �ٸ�. ǥ�õ��� �ʽ��ϴ�.
		   (Parent Actor �� Child Actor �� ������Ʈ�ؾ��ϴ� �ǹ��� �����ϴ�.)
* @author Yang Kyowon
* @data 2016-08-16
* @latestdata 2016-08-16
* @latestmodifier Yang Kyowon
*/

#pragma once
#include <string>
#include <vector>
using string = std::wstring;;

class AoLevel;
class AoComponent;
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
	AoActor();
	~AoActor();

	void AttachChild( AoActor* const Child );
	void DetachChild( AoActor* const Child );
	AoActor* DetachChild( const string& Name );
	void DetachAllChild( bool bIsCleanup = true );

	void AttachComponent( AoComponent* const Component );
	void DetachComponent( AoComponent* const Component );
	void DetachAllComponent( bool bIsCleanup = true );

	static uint64_t GetInstanceCount();
	string GetName() const;

	AoActor* GetParent() const;
	AoLevel* GetRegisteredLevel() const;

	virtual void Tick( float DeltaTime ) { }

	void SetActive( bool bIsActive );
	/** Scene �� ��ϵǾ������� �˻���. */
	bool IsActive() const;

private:
	friend AoLevel;
	virtual void Update( float DeltaTime ) final;

	void SetParent( AoActor* const Parent );
	void SetRegisteredLevel( AoLevel* const TargetLevel );

protected:
	bool bIsActive;
	bool bIsTick;

private:
	static uint64_t InstanceCount;
	string Name;

	ActorVector Children;

	AoActor* Parent;
	AoLevel* RegisteredLevel;

	ComponentVector Components;

};