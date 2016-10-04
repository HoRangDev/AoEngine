#include "AoCameraComponent.h"
#include "AoActor.h"
#include "AoTransform.h"
#include "AoMath.h"
#include "AoMatrix4x4.h"
#include "AoVector4.h"

AoCameraComponent::AoCameraComponent( )
{
}

AoCameraComponent::~AoCameraComponent( )
{
}

float AoCameraComponent::GetNear( ) const
{
	return Near;
}

void AoCameraComponent::SetNear( float Near )
{
	this->Near = Max<float>( Near, 0.0f );
}

float AoCameraComponent::GetFar( ) const
{
	return Far;
}

void AoCameraComponent::SetFar( float Far )
{
	this->Far = Far;
}

float AoCameraComponent::GetFOV( ) const
{
	return FOV;
}

void AoCameraComponent::SetFOV( float FOV )
{
	this->FOV = Clamp<float>( FOV, 5.0f, 170.0f );
}

float AoCameraComponent::GetAspectRatio( ) const
{
	return AspectRatio;
}

void AoCameraComponent::SetAspectRatio( float AspectRatio )
{
	this->AspectRatio = Clamp<float>( AspectRatio, 1.0f, 2.5f );
}

AoMatrix4x4 AoCameraComponent::GetViewMatrix( ) const
{
	AoTransform* Transform = Actor->GetTransform( );
	AoVector4 LookDirection{ 0.0f, 0.0f, 1.0f, 0.0f };
	LookDirection = LookDirection * Transform->GetRelativeRotationMatrix( );
	return AoMatrix4x4::CreateLookToLH(
		Transform->GetRelativePosition( ),
		AoVector( LookDirection.X, LookDirection.Y, LookDirection.Z ),
		AoVector( 0.0f, 1.0f, 0.0f ) );
}

AoMatrix4x4 AoCameraComponent::GetProjectionMatrix( ) const
{
	return AoMatrix4x4::CreatePerspectiveLH( FOV, AspectRatio, Near, Far );
}

AoMatrix4x4 AoCameraComponent::GetViewProjMatrix( ) const
{
	return GetViewMatrix( ) * GetProjectionMatrix( );
}