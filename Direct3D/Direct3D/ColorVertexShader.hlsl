cbuffer MatrixBuffer
{
    float4x4 worldViewProjectionMatrix;
};

struct VertexInput
{
	float4 position : POSITION;
	float4 color	: COLOR;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;
};

VertexOutput main(VertexInput IN)
{
	VertexOutput OUT;

	// homogeneouse 
    IN.position.w = 1.0;
    OUT.position = mul(IN.position, worldViewProjectionMatrix);
	OUT.color = IN.color;

	return OUT;
}