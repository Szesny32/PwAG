cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj;
	float3 gCameraPosition;
};

struct VertexData
{
	float3 PosL  : POSITION;
	float2 UV : TEXCOORD;
};

/*----------------VERTEX SHADER------------------------------------------*/
VertexData VS_Main(VertexData vin)
{
	VertexData vout;
	vout.PosL = vin.PosL;
	vout.UV = vin.UV;
	
	return vout;
}

struct PatchTess
{
	float EdgeTess[4] : SV_TessFactor;
	float InsideTess[2] : SV_InsideTessFactor;
};

/*----------------CONSTANT HULL SHADER------------------------------------------*/
PatchTess ConstantHS(InputPatch<VertexData, 4> patch, uint patchID:SV_PrimitiveID)
{
	//Zadanie 2.1 - zmodyfikuj wspolczynniki teselacji

	float n = 150.0f / ceil(length(gCameraPosition) + 0.0001f);

	PatchTess patchTess;
	patchTess.EdgeTess[0] = n;
	patchTess.EdgeTess[1] = n;
	patchTess.EdgeTess[2] = n;
	patchTess.EdgeTess[3] = n;

	patchTess.InsideTess[0] = n;
	patchTess.InsideTess[1] = n;

	return patchTess;
}

struct HullOut
{
	float3 PosL : POSITION;
	float2 uv : TEXCOORD0;
};

/*----------------HULL SHADER------------------------------------------*/
[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("ConstantHS")]
[maxtessfactor(64.0f)]
HullOut HS_Main(InputPatch<VertexData, 4>p, uint i:SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
	HullOut hout;
	hout.PosL = p[i].PosL;
	hout.uv = p[i].UV;
	return hout;
}

struct DomainOut
{
	float4 PosH : SV_POSITION;
	float2 uv : TEXCOORD0;
};

/*----------------DOMAIN SHADER------------------------------------------*/
Texture2D    gTexture1 : register(t0);
SamplerState gSampler1  : register(s0);
[domain("quad")]
DomainOut DS_Main(PatchTess patchTess, float2 uv : SV_DomainLocation, const OutputPatch<HullOut, 4> quad)
{
	DomainOut dout;

	//Vertex position
	float3 v1 = lerp(quad[0].PosL, quad[1].PosL, uv.x);
	float3 v2 = lerp(quad[3].PosL, quad[2].PosL, uv.x);
	float3 p = lerp(v1, v2, uv.y);

	



	//Texture coordinate
	float2 uv_v1 = lerp(quad[0].uv, quad[1].uv, uv.x);
	float2 uv_v2 = lerp(quad[3].uv, quad[2].uv, uv.x);
	float2 p_uv = lerp(uv_v1, uv_v2, uv.y);


	float4 grayscale = gTexture1.SampleLevel(gSampler1, p_uv, 0);
	float height = (grayscale.r + grayscale.g + grayscale.b) / 3.0;
	float scale = 0.5f;
	p.y = height * scale;




	//Transform to the world view proj coordinates
	dout.PosH = mul(float4(p, 1.0f), gWorldViewProj);;

	//dout.uv = 0.0f; //Zadanie 2.3 wpolrzedne UV
	dout.uv = p_uv;
	
	return dout;
}


/*----------------PIXEL SHADER------------------------------------------*/
float4 PS_Main(DomainOut pin) : SV_Target
{
	//return  float4(1.0f, 0.0f, 0.0f, 1.0f); //Zadanie 2.3 wpolrzedne UV
	return gTexture1.Sample(gSampler1, pin.uv);
}