//Zadanie 2.1.3 program cieniujacy wierzcholki i piksele
struct VertexIn
{
	float3 PosL  : POSITION;
	float3 ColL  : COLOR;
	//dodaj kolor
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	float4 ColH  : COLOR;
	//dodaj kolor
};

VertexOut VS_Main(VertexIn vin)
{
	VertexOut vout;

	// Zadanie 2.2.5 - program cieniujacy wierzcholki
	//Zamiast umieszczonej ponizej statycznej macierzy
	//wykorzystaj macierze zapisane przez ciebie w buforze stalych
	float4x4 worldViewProjection = float4x4(
		2.41, 0.00, 0.00, 0.00,
		0.00, 2.41, 0.00, 0.00,
		0.00, 0.00, 1.00, 1.00,
		0.00, 0.00, 4.00, 5.00
	);

	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), worldViewProjection);
	vout.ColH = float4(vin.ColL, 1.0f);

	return vout;
}

float4 PS_Main(VertexOut pin) : SV_Target
{
	return pin.ColH; //Zadanie 2.1.3 wyswietl kolor
}