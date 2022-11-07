#include "BasicShaderHeader.hlsli"

static const uint vnum = 4;

static const float4 offset_arrey[vnum] = {
	float4(-0.5f,-0.5f,0,0),	//����
	float4(-0.5f,+0.5f,0,0),	//����
	float4(+0.5f,-0.5f,0,0),	//�E��
	float4(+0.5f,+0.5f,0,0)		//�E��
};

static const float2 uv_arrey[vnum] = {
	float2(0,1),	//����
	float2(0,0),	//����
	float2(1,1),	//�E��
	float2(1,0)		//�E��
};

[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;

	//4���_�܂킷
	for (uint i = 0; i < vnum; i++) {
		//���[���h���W�x�[�X�ŁA���炷
		element.svpos = input[0].pos + offset_arrey[i];
		//�r���[�A�ˉe�ϊ�
		element.svpos = mul(mat, element.svpos);
		//element.uv = float2(0.5f, 0.5f);
		element.uv = uv_arrey[i];
		output.Append(element);
	}
}