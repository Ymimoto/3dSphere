#pragma once

// directXTK�ɂ�鋅�̕\��
#include <GeometricPrimitive.h>

using namespace DirectX;


class drawSphere {
public:
	XMMATRIX                g_World;
	XMMATRIX                g_View;
	XMMATRIX                g_Projection;
	std::unique_ptr<GeometricPrimitive>        g_Shape[1];
	drawSphere(); // �������͂������
	~drawSphere();
	void Render(); // ���[�v����
};

