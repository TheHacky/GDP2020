cbuffer MatrixBuffer
{
	matrix	viewProjectionMatrix;
	matrix	worldMatrix;
	float3	cameraWorldPosition;
};

struct VertexInput
{
	float4	position : POSITION;
	float2	uv : TEXCOORD;
	float4	normal : NORMAL;
};

struct VertexOutput
{
	float4	position : SV_POSITION;
    float3 positionWorld : POSITION1;
	float2	uv : TEXCOORD0;
	float3	normal : NORMAL;
	float3	view : TEXCOORD1;
};

VertexOutput main(VertexInput _input)
{
	VertexOutput output;

	_input.position.w = 1.0f;
	float4 positionWorld = mul(_input.position, worldMatrix);
	output.position = mul(positionWorld, viewProjectionMatrix);
    output.positionWorld = positionWorld.xyz;

	output.uv = _input.uv;
	
	// world normal
    _input.normal.w = 0.0f;
    output.normal = mul(_input.normal, worldMatrix);
	
	// view vector
    output.view = cameraWorldPosition;
	
	return output;
}