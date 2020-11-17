cbuffer MatrixBuffer
{
	matrix worldViewProjectionMatrix;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VertexOutput main(float4 position : POSITION, float2 uv : TEXCOORD)
{
	VertexOutput output;

	// transform position directly from local space to projection
	position.w = 1.0f; // homogenous coordinates
	output.position = mul(position, worldViewProjectionMatrix);

    output.uv = uv * float2(1.0f, 1.0f) + float2(0.0f, 0.0f); // tiling & offset

	return output;
}