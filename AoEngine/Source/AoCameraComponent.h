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
	void SetFOV( float FOV );

	float GetAspectRatio( ) const;
	void SetAspectRatio( float AspectRatio );

	AoMatrix4x4 GetViewMatrix( ) const;
	AoMatrix4x4 GetProjectionMatrix( ) const;
	AoMatrix4x4 GetViewProjMatrix( ) const;

private:
	float Near, Far;
	float FOV;
	float AspectRatio;
	
};