struct VertexIn
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
	float2 TextureUV : TEXCOORD;
	float3 Tangent : TANGENT;
	float3 BiNormal : BINORMAL;
};

struct Fragment
{
	float4 Position : SV_POSITION;
	float3 WorldPosition : POSITION;
	float2 TextureUV : TEXCOORD0;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 BiNormal : BINORMAL;
};