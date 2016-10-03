#include "AoTransform.h"
#include "AoActor.h"

AoTransform::AoTransform( ) 
	: AoTransform( AoVector::Zero, AoVector::One, AoVector::Zero )
{
}

AoTransform::AoTransform( const AoVector& Position, const AoVector& Scale, const AoVector& Rotation )
	: Position( Position ),
	Scale( Scale ),
	Rotation( Rotation ),
	Parent( nullptr )
{
}

AoTransform::~AoTransform( )
{
}

void AoTransform::OnAttach( )
{
	AoActor* ParentActor = Actor->GetParent( );
	if( ParentActor != nullptr )
	{
		Parent = ParentActor->GetTransform( );
	}
}

void AoTransform::OnDetach( )
{
	Parent = nullptr;
}

void AoTransform::SetPosition( const AoVector& Position )
{
	this->Position = Position;
}

void AoTransform::SetScale( const AoVector& Scale )
{
	this->Scale = Scale;
}

void AoTransform::SetRotation( const AoVector& Rotation )
{
	this->Rotation = Rotation;
}

void AoTransform::SetRotationX( float Degree )
{
	this->Rotation.X = Degree;
}

void AoTransform::SetRotationY( float Degree )
{
	this->Rotation.Y = Degree;
}

void AoTransform::SetRotationZ( float Degree )
{
	this->Rotation.Z = Degree;
}

AoVector AoTransform::GetPosition( ) const
{
	return Position;
}

AoVector AoTransform::GetRelativePosition( ) const
{
	if( Parent != nullptr )
	{
		return Parent->GetRelativePosition( ) + Position;
	}

	return Position;
}

AoVector AoTransform::GetScale( ) const
{
	return this->Scale;
}

AoVector AoTransform::GetRelativeScale( ) const
{
	if( Parent != nullptr )
	{
		return Parent->GetRelativeScale( ) + Scale;
	}

	return Scale;
}

AoVector AoTransform::GetRotation( ) const
{
	return Rotation;
}

AoVector AoTransform::GetRelativeRotation( ) const
{
	if( Parent != nullptr )
	{
		return Parent->GetRelativeRotation( ) + Rotation;
	}

	return Rotation;
}

float AoTransform::GetRotationX( ) const
{
	return Rotation.X;
}

float AoTransform::GetRelativeRotationX( ) const
{
	return GetRelativeRotation( ).X;
}

float AoTransform::GetRotationY( ) const
{
	return Rotation.Y;
}

float AoTransform::GetRelativeRotationY( ) const
{
	return GetRelativeRotation( ).Y;
}

float AoTransform::GetRotationZ( ) const
{
	return Rotation.Z;
}

float AoTransform::GetRelativeRotationZ( ) const
{
	return GetRelativeRotation( ).Z;
}

AoMatrix4x4 AoTransform::GetTranslationMatrix( ) const
{
	return AoMatrix4x4::CreateTranslationMatrix( Position );
}

AoMatrix4x4 AoTransform::GetRelativeTranslationMatrix( ) const
{
	AoVector RelativePosition = GetRelativePosition( );
	return AoMatrix4x4::CreateTranslationMatrix( RelativePosition );
}

AoMatrix4x4 AoTransform::GetScaleMatrix( ) const
{
	return AoMatrix4x4::CreateScaleMatrix( Scale );
}

AoMatrix4x4 AoTransform::GetRelativeScaleMatrix( ) const
{
	AoVector RelativeScale = GetRelativeScale( );
	return AoMatrix4x4::CreateScaleMatrix( RelativeScale );
}

AoMatrix4x4 AoTransform::GetRotationMatrix( ) const
{
	return AoMatrix4x4::CreateRotation( Rotation );
}

AoMatrix4x4 AoTransform::GetRelativeRotationMatrix( ) const
{
	return AoMatrix4x4::CreateRotation( GetRelativeRotation( ) );
}

AoMatrix4x4 AoTransform::GetTransformationMatrix( ) const
{
	return GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix( );
}

AoMatrix4x4 AoTransform::GetRelativeTransformationMatrix( ) const
{
	return GetRelativeScaleMatrix( ) * GetRelativeRotationMatrix( ) * GetRelativeTranslationMatrix( );
}

void AoTransform::SetParent( AoTransform* Parent )
{
	this->Parent = Parent;
}

AoTransform* AoTransform::GetParent( ) const
{
	return Parent;
}
