#include "AoComponent.h"
#include "AoActor.h"

AoComponent::AoComponent()
{

}

AoComponent::~AoComponent()
{

}

void AoComponent::SetActive( bool bIsActive )
{
	this->bIsActive = bIsActive;
}

bool AoComponent::IsActive() const
{
	return bIsActive;
}

AoActor* AoComponent::GetAttachedActor() const
{
	return Actor;
}

void AoComponent::SetAttachedActor( AoActor* Actor )
{
	this->Actor = Actor;
}