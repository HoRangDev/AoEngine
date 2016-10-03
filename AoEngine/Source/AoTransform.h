#pragma once
#include "AoComponent.h"
#include "AoMatrix4x4.h"
#include "AoVector.h"

class AoTransform : public AoComponent
{
public:
	AoTransform( );
	AoTransform( const AoVector& Position, const AoVector& Scale, const AoVector& Rotation );
	~AoTransform( );

	virtual void OnAttach( ) override;
	virtual void OnDetach( ) override;

	void SetPosition( const AoVector& Position );
	void SetScale( const AoVector& Scale );
	void SetRotation( const AoVector& Rotation );
	void SetRotationX( float Degree );
	void SetRotationY( float Degree );
	void SetRotationZ( float Degree );

	AoVector GetPosition( ) const;
	AoVector GetRelativePosition( ) const;
	AoVector GetScale( ) const;
	AoVector GetRelativeScale( ) const;
	AoVector GetRotation( ) const;
	AoVector GetRelativeRotation( ) const;
	float GetRotationX( ) const;
	float GetRelativeRotationX( ) const;
	float GetRotationY( ) const;
	float GetRelativeRotationY( ) const;
	float GetRotationZ( ) const;
	float GetRelativeRotationZ( ) const;

	AoMatrix4x4 GetTranslationMatrix( ) const;
	AoMatrix4x4 GetRelativeTranslationMatrix( ) const;
	AoMatrix4x4 GetScaleMatrix( ) const;
	AoMatrix4x4 GetRelativeScaleMatrix( ) const;
	AoMatrix4x4 GetRotationMatrix( ) const;
	AoMatrix4x4 GetRelativeRotationMatrix( ) const;
	AoMatrix4x4 GetTransformationMatrix( ) const;
	AoMatrix4x4 GetRelativeTransformationMatrix( ) const;

	void SetParent( AoTransform* Parent );
	AoTransform* GetParent( ) const;

private:
	AoTransform* Parent;
	AoVector Position;
	AoVector Scale;
	AoVector Rotation;

};