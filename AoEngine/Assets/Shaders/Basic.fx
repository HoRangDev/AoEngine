cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gViewProj;
};

struct VertexIn
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
	float2 TextureUV : TEXCOORD;
	float3 Tangent : TANGENT;
	float3 BiNormal : BINORMAL;
};

struct VertexOut
{
	float4 Position : SV_POSITION;
	float3 WorldPosition : POSITION;
	float3 Diffuse : TEXCOORD1;
};

VertexOut VS( VertexIn VIn )
{
	VertexOut VOut;
	VOut.WorldPosition = mul( float4( VIn.Position, 1.0f ), gWorld ).xyz;

	float3 LightDir = VOut.WorldPosition - float3( 500.0f, 500.0f, -500.0f );
	LightDir = normalize( LightDir );

	float3 WorldNormal = mul( VIn.Normal, (float3x3)gWorld );
	WorldNormal = normalize( WorldNormal );

	VOut.Position = mul( float4( VIn.Position, 1.0f ), mul( gWorld, gViewProj ) );
	VOut.Diffuse = dot( -LightDir, WorldNormal );

	return VOut;
}

float4 PS( VertexOut VOut ) : SV_Target
{
	float3 Diffuse = saturate( VOut.Diffuse );
	return float4( Diffuse, 1.0f );
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