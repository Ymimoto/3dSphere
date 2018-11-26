#include "stdafx.h"
#include "drawSphere.h"


drawSphere::drawSphere() {
	// 今回はワールド空間は変わらないため、ここで情報をつくってしまおう

	// DirectXTKオブジェクトの作成
	g_Shape[0] = GeometricPrimitive::CreateSphere(g_pImmediateContext, 3.0f, 8, false, false);
	g_Shape[1] = GeometricPrimitive::CreateGeoSphere(g_pImmediateContext, 3.0f, 2, false);

	// ワールドマトリックスの初期化
	g_World = XMMatrixIdentity();

	// ビューマトリックスの初期化
	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	// プロジェクションマトリックスの初期化
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
}


drawSphere::~drawSphere() {
}
