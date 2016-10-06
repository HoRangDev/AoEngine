#include "AoCameraComponent.h"
#include "AoActor.h"
#include "AoTransform.h"
#include "AoMath.h"
#include "AoMatrix4x4.h"
#include "AoVector4.h"
#include "AoRenderer.h"

AoCameraComponent::AoCameraComponent( )
	: bIsDirty( true ), Near( 1.0f ), Far( 1000.0f ),
	FOV( 70.0f ), AspectRatio( 1.0f )
{
}

AoCameraComponent::~AoCameraComponent( )
{
	if ( AoRenderer::GetInstance( ).GetMainCamera( ) == this )
	{
		AoRenderer::GetInstance( ).SetMainCamera( nullptr );
	}
}

float AoCameraComponent::GetNear( ) const
{
	return Near;
}

void AoCameraComponent::SetNear( float Near )
{
	this->Near = Max<float>( Near, 0.0f );
	this->bIsDirty = true;
}

float AoCameraComponent::GetFar( ) const
{
	return Far;
}

void AoCameraComponent::SetFar( float Far )
{
	this->Far = Far;
	this->bIsDirty = true;
}

float AoCameraComponent::GetFOV( ) const
{
	return FOV;
}

void AoCameraComponent::SetFOV( float DegreeFOV )
{
	this->FOV = Clamp<float>( DegreeFOV, 5.0f, 170.0f );
	this->bIsDirty = true;
}

float AoCameraComponent::GetAspectRatio( ) const
{
	return AspectRatio;
}

void AoCameraComponent::SetAspectRatio( float AspectRatio )
{
	this->AspectRatio = Clamp<float>( AspectRatio, 1.0f, 2.5f );
	this->bIsDirty = true;
}

AoMatrix4x4 AoCameraComponent::GetViewMatrix( )
{
	if ( IsDirty() )
	{
		AoTransform* Transform = Actor->GetTransform( );
		AoVector4 LookDirection{ 0.0f, 0.0f, 1.0f, 0.0f };
		LookDirection = LookDirection * Transform->GetRelativeRotationMatrix( );
		ViewMatrix = AoMatrix4x4::CreateLookToLH(
			Transform->GetRelativePosition( ),
			AoVector( LookDirection.X, LookDirection.Y, LookDirection.Z ),
			AoVector( 0.0f, 1.0f, 0.0f ) );
	}

	return ViewMatrix;
}

AoMatrix4x4 AoCameraComponent::GetProjectionMatrix( )
{
	if ( IsDirty() )
	{
		ProjectionMatrix = AoMatrix4x4::CreatePerspectiveLH( FOV, AspectRatio, Near, Far );
	}

	return ProjectionMatrix;
}

AoMatrix4x4 AoCameraComponent::GetViewProjMatrix( )
{
	if ( IsDirty() )
	{
		ViewProjectionMatrix = GetViewMatrix() * GetProjectionMatrix();
	}

	return ViewProjectionMatrix;
}

bool AoCameraComponent::IsDirty( ) const
{
	return bIsDirty || Actor->GetTransform( )->IsDirty( );
}

void AoCameraComponent::SetDirty( bool bIsDirty )
{
	this->bIsDirty = bIsDirty;
	Actor->GetTransform( )->SetDirty( bIsDirty );
}
