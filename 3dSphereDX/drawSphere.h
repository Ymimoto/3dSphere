#pragma once

// directXTKによる球体表示
#include <GeometricPrimitive.h>

using namespace DirectX;


class drawSphere {
public:
	XMMATRIX                g_World;
	XMMATRIX                g_View;
	XMMATRIX                g_Projection;
	std::unique_ptr<GeometricPrimitive>        g_Shape[1];
	drawSphere(); // 初期化はこちらで
	~drawSphere();
	void Render(); // ループ処理
};

