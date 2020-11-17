Texture2D mainTexture;
sampler mainSampler;

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

float4 main(PixelInput input) : SV_TARGET
{
    float4 color = mainTexture.Sample(mainSampler, input.uv);
    
    //color = 1 - color; // invert
    //color.r = 0; // eliminate red
    //color = color * 0.5f; // brightness
    
    //clip(color.g - 0.5f); // dsicarding pixel relating on value
    //clip(color.a - 0.9999999f); // alpha clipping
    
    return color;
}