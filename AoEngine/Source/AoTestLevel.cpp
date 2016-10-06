#include "AoTestLevel.h"
#include "AoAssetManager.h"
#include "AoModel.h"
#include "AoActor.h"
#include "AoMeshRenderComponent.h"
#include "AoTransform.h"
#include "AoRenderer.h"
#include "AoMaterial.h"
#include "AoMaterialManager.h"
#include "AoCameraComponent.h"

AoTestLevel::AoTestLevel( )
{
	Initialize( );
}

AoTestLevel::~AoTestLevel( )
{
}

void AoTestLevel::Initialize( )
{
	AoRenderer& Renderer = AoRenderer::GetInstance( );
	Camera = new AoActor( TEXT( "MainCamera" ) );
	AoCameraComponent* CameraComponent = new AoCameraComponent( );
	CameraComponent->SetAspectRatio( 1.75f );
	CameraComponent->SetFOV( 70.0f );
	CameraComponent->SetNear( 1.0f );
	CameraComponent->SetFar( 1000.0f );
	Camera->AttachComponent( CameraComponent );
	Renderer.SetMainCamera( CameraComponent );
	Camera->GetTransform( )->SetPosition( AoVector( 0.0f, 50.0f, -10.0f ) );
	this->RegisterActor( Camera );

	Model = dynamic_cast< AoModel* >( AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Models" ), TEXT( "unitychan" ), TEXT( ".fbx" ) ) );

	UnityChan = AoModel::ModelToActor( Model, UnityChanRenderComponent );
	UnityChan->GetTransform( )->SetPosition( AoVector( 0.0f, 0.0f, 150.0f ) );
	this->RegisterActor( UnityChan );

	AoMaterialManager::GetInstance( ).RegisterMaterial( dynamic_cast< AoMaterial* >(
		AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Materials" ), 
		TEXT( "Basic" ),
		TEXT( ".material" ) ) ) );
}