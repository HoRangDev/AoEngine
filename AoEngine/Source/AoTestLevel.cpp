#include "AoTestLevel.h"
#include "AoAssetManager.h"
#include "AoModel.h"
#include "AoTestActor.h"
#include "AoMeshRenderComponent.h"
#include "AoTransform.h"
#include "AoRenderer.h"
#include "AoMaterial.h"
#include "AoMaterialManager.h"
#include "AoCameraComponent.h"
#include "AoTexture2D.h"
#include "AoLightComponent.h"
#include "AoLight.h"
#include "AoLightManager.h"

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
	Camera->GetTransform( )->SetPosition( AoVector( 0.0f, 0.0f, -10.0f ) );
	this->RegisterActor( Camera );

	Model = dynamic_cast< AoModel* >( AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Models" ), TEXT( "Sphere" ), TEXT( ".3ds" ) ) );

	Sphere = AoModel::ModelToActor<AoTestActor>( Model, RenderComponents );
	Sphere->GetTransform( )->SetPosition( AoVector( 0.0f, 0.0f, 180.0f ) );
	Sphere->GetTransform( )->SetScale( AoVector( 1.0f, 1.0f, 1.0f ) );
	Sphere->GetTransform( )->SetRotationX( 90.0f );
	this->RegisterActor( Sphere );

	AoMaterial* Material = dynamic_cast< AoMaterial* >(
		AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Materials" ),
		TEXT( "Basic" ),
		TEXT( ".material" ) ) );
	AoMaterialManager::GetInstance( ).RegisterMaterial( Material );

	DiffuseMap = dynamic_cast< AoTexture2D* >(
		AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Textures" ),
		TEXT( "photosculpt-graystonewall-diffuse" ),
		TEXT( ".jpg" ) ) );

	SpecularMap = dynamic_cast< AoTexture2D* >(
		AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Textures" ),
		TEXT( "photosculpt-graystonewall-specular" ),
		TEXT( ".jpg" ) ) );

	NormalMap = dynamic_cast< AoTexture2D* >(
		AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Textures" ),
		TEXT( "photosculpt-graystonewall-normal" ),
		TEXT( ".jpg" ) ) );

	Material->SetTextureByName( TEXT( "DiffuseMap" ), DiffuseMap );
	Material->SetTextureByName( TEXT( "SpecularMap" ), SpecularMap );
	Material->SetTextureByName( TEXT( "NormalMap" ), NormalMap );

	AoActor* LightActor = new AoActor( TEXT( "MainLight" ) );

	AoLight LightData;
	LightData.SetDiffuse( AoVector4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	LightData.SetAmbient( AoVector4( 0.05f, 0.05f, 0.05f, 0.0f ) );
	LightData.SetSpecularExponent( 20.0f );
	LightData.SetPosition( AoVector( 500.0f, 500.0f, -500.0f ) );
	AoLightComponent* LightComponent = new AoLightComponent( LightData );
	LightActor->AttachComponent( LightComponent );
	AoLightManager::GetInstance( ).RegisterLight( LightComponent, 0 );
	this->RegisterActor( LightActor );
}