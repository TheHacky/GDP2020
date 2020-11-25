Texture2D mainTexture;
SamplerState mainSampler;

cbuffer LightBuffer
{
	float4	ambientColor;
	float4	specularColor;
	float4	lightColor;
	float3	lightVector;
	float	lightIntensity;
};

struct PixelInput
{
	float4	position : SV_POSITION;
    float3 positionWorld : POSITION1;
    float2 uv : TEXCOORD0;
	float3	normal : NORMAL;
	float3	view : TEXCOORD1;
};

float4 main(PixelInput _input) : SV_TARGET
{
	float4 c = 0;

	float4 tex = mainTexture.Sample(mainSampler, _input.uv);
	
	// normalizing values
    float3 normal = normalize(_input.normal);
    float3 light = normalize(lightVector);
    float3 view = normalize(_input.view - _input.positionWorld);
	
    // diffuse color - lambert
    float4 diffuseColor = 0;
    float diffuse = max(0.0f, dot(-light, normal));
    diffuseColor = lightColor * (diffuse * lightIntensity);
	
	// specular color
    float4 specularC = 0;
    
	if (diffuse > 0.0f) // only neccessary if you want to draw back faces
    {
		// phong
        float3 reflectV = reflect(light, normal);
        float specular = pow(max(0.0f, dot(reflectV, view)), 256.0f);
	
		// blinn-phong
        //float3 halfV = (view - light) * 0.5f;
        //float specular = pow(max(0.0f, dot(halfV, normal)), 128.0f);
        
		specularC = specularColor * specular;
    }
	
	// return color calculation
    c = saturate(tex * saturate(ambientColor + diffuseColor) + 
		specularC/* + float4(1.0f, 0.0f, 0.0f, 1.0f)*/);

    return c;
}