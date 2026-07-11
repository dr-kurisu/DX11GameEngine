struct VSInput
{
    float3 position : POSITION0;
    float4 colour : COLOUR0;
};

cbuffer ConstantData : register(b0)
{
    row_major float4x4 world;
}

struct VSOutput
{
    float4 position : SV_Position;
    float4 colour : COLOUR0;
};

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.position = mul(float4(input.position, 1), world);
    output.colour = input.colour;
    return output;
}

float4 PSMain(VSOutput input) : SV_Target
{
    return input.colour;
}