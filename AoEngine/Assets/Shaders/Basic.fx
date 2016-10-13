#include "Lights.fx"
// @TODO: Add World-Inverse-Transpose matrix for world normal transform.
// @TODO: Phong-Blin Shading

#define MAX_LIGHT_NUM 8

cbuffer ConstantBufferPerFrame
{
	Light Lights[ MAX_LIGHT_NUM ];
	int BindingLightsNumber;

	float4 WorldCameraPosition;

	float FogStart;
	float FogRange;
	float4 FogColor;
	bool IsFoggy;
};

cbuffer ConstantBufferPerObject
{
	float4x4 WorldMatrix;
	float4x4 ViewProjMatrix;
};

// Textures
Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;

SamplerState DefaultSampler
{
	AddressU = WRAP;
	AddressV = WRAP;
};

Fragment VS( VertexIn Input )
{
	Fragment Output;

	Output.Position = mul( float4( Input.Position, 1.0f ), mul( WorldMatrix, ViewProjMatrix ) );
	Output.TextureUV = Input.TextureUV;

	Output.WorldPosition = mul( float4( Input.Position, 1.0f ), WorldMatrix ).xyz;

	// It isn't caculate Light Direction for multiple Lights.
	// Translation is unnecessary in direction vector.
	float3 WorldNormal = mul( Input.Normal, ( float3x3 )WorldMatrix );
	Output.Normal = normalize( WorldNormal );

	float3 WorldTangent = mul( Input.Tangent, ( float3x3 )WorldMatrix );
	Output.Tangent = normalize( WorldTangent );

	float3 WorldBiNormal = mul( Input.BiNormal, ( float3x3 )WorldMatrix );
	Output.BiNormal = normalize(WorldBiNormal);

	return Output;
}

float4 PS( Fragment Input ) : SV_Target
{
	float3 FinalAmbient = float3( 0.0f, 0.0f, 0.0f );
	float3 FinalDiffuse = float3( 0.0f, 0.0f, 0.0f );
	float3 FinalSpecular = float3( 0.0f, 0.0f, 0.0f );

	[unroll]
	for( int Index = 0; Index < BindingLightsNumber; ++Index )
	{
		float3 Ambient = float3( 0.0f, 0.0f, 0.0f );
		float3 Diffuse = float3( 0.0f, 0.0f, 0.0f );
		float3 Specular = float3( 0.0f, 0.0f, 0.0f );

		ComputeLight( Input, Lights[ Index ], WorldCameraPosition.xyz,
			DiffuseMap, DefaultSampler,
			SpecularMap, DefaultSampler,
			NormalMap, DefaultSampler,
			Ambient, Diffuse, Specular );

		FinalAmbient += Ambient;
		FinalDiffuse += Diffuse;
		FinalSpecular += Specular;
	}

	return float4( FinalAmbient + FinalDiffuse + FinalSpecular, 1.0f );
}

technique11 Basic
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_5_0, VS( ) ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, PS( ) ) );
	}
}