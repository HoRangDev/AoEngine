#pragma once
#include "AoComponent.h"
#include "AoVector2.h"
#include "AoMatrix4x4.h"

class AoTransform;
class AoCameraComponent : public AoComponent
{
public:
	AoCameraComponent( );
	~AoCameraComponent( );

	float GetNear( ) const;
	void SetNear( float Near );

	float GetFar( ) const;
	void SetFar( float Far );

	float GetFOV( ) const;
	void SetFOV( float DegreeFOV );

	float GetAspectRatio( ) const;
	void SetAspectRatio( float AspectRatio );

	AoMatrix4x4 GetViewMatrix( );
	AoMatrix4x4 GetProjectionMatrix( );
	AoMatrix4x4 GetViewProjMatrix( );

	bool IsDirty( ) const;
	void SetDirty( bool bIsDirty );

private:
	bool bIsDirty;
	float Near, Far;
	float FOV;
	float AspectRatio;

	AoMatrix4x4 ViewMatrix;
	AoMatrix4x4 ProjectionMatrix;
	AoMatrix4x4 ViewProjectionMatrix;
	
};