#include "ShaderStructure.fx"

struct Light
{
	float4 Ambient;
	float4 Diffuse;
	float3 Specular;
	float SpecularExponent;

	float3 Position;
	float Range;

	float3 Direction;
	float SpotExponent;

	float ConstantAttenuation;
	float LinearAttenuation;
	float QuadraticAttenuation;
	int LightType;
};

void ComputeLight( Fragment Input, Light Target, float3 CameraPosition,
	Texture2D DiffuseMap,
	SamplerState DiffuseSampler,
	Texture2D SpecularMap,
	SamplerState SpecularSampler,
	Texture2D NormalMap,
	SamplerState NormalSampler,
	out float3 TargetAmbient,
	out float3 TargetDiffuse,
	out float3 TargetSpecular )
{
	TargetAmbient = float3( 0.0f, 0.0f, 0.0f );
	TargetDiffuse = float3( 0.0f, 0.0f, 0.0f );
	TargetSpecular = float3( 0.0f, 0.0f, 0.0f );

	float3 TangentNormal = NormalMap.Sample( NormalSampler, Input.TextureUV ).xyz;
	// [ -1.0, 1.0 ]
	TangentNormal = normalize( TangentNormal * 2.0f - 1.0f );

	float3x3 TBN = float3x3(
		normalize( Input.Tangent ),
		normalize( Input.BiNormal ), 
		normalize( Input.Normal ) );
	TBN = transpose( TBN ); // Inverse of TBN

	float3 WorldNormal = mul( TBN, TangentNormal );

	// Phong(Lambert Cosine law) Diffuse
	float4 Albedo = DiffuseMap.Sample( DiffuseSampler, Input.TextureUV );
	float3 LightDir = normalize( Input.WorldPosition.xyz - Target.Position.xyz );
	float3 Diffuse = saturate( dot( WorldNormal, -LightDir ) );
	Diffuse = Diffuse.rgb * Albedo.rgb * Diffuse;

	// Blin Specular( Half Way )
	float3 Specular = 0.0f;
	if( Diffuse.x > 0.0f )
	{
		float3 ToEye = CameraPosition.xyz - Input.WorldPosition.xyz;
		ToEye = normalize( ToEye );
		float3 HalfWay = normalize( ToEye + ( -LightDir ) );

		Specular = saturate( dot( HalfWay, WorldNormal ) );
		Specular = pow( Specular, Target.SpecularExponent );

		float4 SpecularIntensity = SpecularMap.Sample( SpecularSampler, Input.TextureUV );
		Specular *= SpecularIntensity.rgb * Specular.rgb;
	}

	float3 Ambient = Target.Ambient.rgb * Albedo.rgb;

	[flatten]
	if ( Target.LightType == 1 )
	{
		// Range based Attenuation
	}
	else if ( Target.LightType == 2 )
	{
		// Range & Cone based Attenuation
	}

	TargetAmbient += Ambient;
	TargetDiffuse += Diffuse;
	TargetSpecular += Specular;
}