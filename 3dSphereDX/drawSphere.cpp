#include "stdafx.h"
#include "drawSphere.h"


drawSphere::drawSphere() {
	// ����̓��[���h��Ԃ͕ς��Ȃ����߁A�����ŏ��������Ă��܂���

	// DirectXTK�I�u�W�F�N�g�̍쐬
	g_Shape[0] = GeometricPrimitive::CreateSphere(g_pImmediateContext, 3.0f, 8, false, false);
	g_Shape[1] = GeometricPrimitive::CreateGeoSphere(g_pImmediateContext, 3.0f, 2, false);

	// ���[���h�}�g���b�N�X�̏�����
	g_World = XMMatrixIdentity();

	// �r���[�}�g���b�N�X�̏�����
	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
}


drawSphere::~drawSphere() {
}
