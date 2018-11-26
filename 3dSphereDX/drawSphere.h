#pragma once

// directXTK‚É‚æ‚é‹…‘Ì•\¦
#include <GeometricPrimitive.h>

using namespace DirectX;


class drawSphere {
public:
	XMMATRIX                g_World;
	XMMATRIX                g_View;
	XMMATRIX                g_Projection;
	std::unique_ptr<GeometricPrimitive>        g_Shape[1];
	drawSphere(); // ‰Šú‰»‚Í‚±‚¿‚ç‚Å
	~drawSphere();
	void Render(); // ƒ‹[ƒvˆ—
};

