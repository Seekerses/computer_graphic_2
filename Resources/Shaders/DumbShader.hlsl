struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

cbuffer VertexConstantBuffer : register(b0)
{
    float4 position;
    float4 rotation;
    float4 scale;
}

PS_IN VSMain( VS_IN input )
{
	PS_IN output = (PS_IN)0;

	output.pos = (input.pos * scale) + position;
	output.col = input.col;

	return output;
}

float4 PSMain( PS_IN input ) : SV_Target
{
	float4 col = input.col + float4(color.xyz, 1);
	return col;
}