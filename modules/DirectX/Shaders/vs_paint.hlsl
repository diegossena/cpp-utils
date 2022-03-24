// -*- mode: hlsl; hlsl-entry: main; hlsl-target: vs_6_0; hlsl-args: ; -*-
struct VSOut
{
    float4 pos: SV_POSITION;
    float4 color : Color;
};

VSOut main(float4 pos : Position, float4 color : Color)
{
    VSOut output;

    output.pos = pos;
    output.color = color;

    return output;
}