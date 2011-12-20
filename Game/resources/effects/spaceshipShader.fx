float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;
float speed;
float maxSpeed;
texture fullSpeedTexture;
texture stoppedTexture;

sampler FullSpeedSampler = sampler_state {
    Texture = <fullSpeedTexture>;
    MinFilter = None;
    MagFilter = None;
    MipFilter = None;
    AddressU  = Clamp;
    AddressV  = Clamp;
};

sampler StoppedSampler = sampler_state {
    Texture = <stoppedTexture>;
    MinFilter = None;
    MagFilter = None;
    MipFilter = None;
    AddressU  = Clamp;
    AddressV  = Clamp;
};

struct VertexShaderInput {
    float3 position : POSITION0;
    float4 color    : COLOR0;
    float2 tex0     : TEXCOORD0;
	float2 tex1     : TEXCOORD1;
};

struct VertexShaderOutput {
    float4 position : POSITION0;
    float4 color    : COLOR0;
	float2 tex0     : TEXCOORD0;
	float2 tex1     : TEXCOORD1;
};

VertexShaderOutput PassthroughVertexShader(VertexShaderInput input)
{
	VertexShaderOutput output;

	output.position = mul( float4(input.position, 1.0f), worldMatrix );
	output.position = mul( output.position, viewMatrix );
	output.position = mul( output.position, projectionMatrix );

	output.color = input.color;
	output.tex0 = input.tex0; 
	output.tex1 = input.tex1;

	return output;
}

float4 InterpolateBetweenTextures(VertexShaderOutput input) : COLOR
{
	float4 stoppedColor = tex2D(StoppedSampler,   input.tex0);
	float4 fullspeedColor = tex2D(FullSpeedSampler, input.tex0);

	return lerp(stoppedColor, fullspeedColor, speed);
}

technique spaceshipShaderTechnique
{
	pass Pass0 {
		vertexshader = compile vs_3_0 PassthroughVertexShader();
		pixelshader = compile ps_3_0 InterpolateBetweenTextures();
	}
}