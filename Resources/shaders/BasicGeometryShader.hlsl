#include "BasicShaderHeader.hlsli"

static const uint vnum = 4;

static const float4 offset_arrey[vnum] = {
	float4(-0.5f,-0.5f,0,0),	//左下
	float4(-0.5f,+0.5f,0,0),	//左上
	float4(+0.5f,-0.5f,0,0),	//右下
	float4(+0.5f,+0.5f,0,0)		//右上
};

static const float2 uv_arrey[vnum] = {
	float2(0,1),	//左下
	float2(0,0),	//左上
	float2(1,1),	//右下
	float2(1,0)		//右上
};

[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;

	//4頂点まわす
	for (uint i = 0; i < vnum; i++) {
		//ワールド座標ベースで、ずらす
		element.svpos = input[0].pos + offset_arrey[i];
		//ビュー、射影変換
		element.svpos = mul(mat, element.svpos);
		//element.uv = float2(0.5f, 0.5f);
		element.uv = uv_arrey[i];
		output.Append(element);
	}
}