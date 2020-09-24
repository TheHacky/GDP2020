struct VertexInput
{
	float3 position : POSITION;
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

	OUT.position = float4(IN.position, 1.0f);
	OUT.color = IN.color;

	return OUT;
}