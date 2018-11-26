#include "stdafx.h"
#include "CameraControll.h"

using namespace DirectX;
using namespace std;

CameraControll::CameraControll() {
	// �e�평����
	m_world = XMMatrixIdentity();
	m_view = XMMatrixIdentity();
	m_projection = XMMatrixIdentity();

	m_eye = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // �����Ȃ��Ƃ��Ȃ����肱�̒l�ł������傤�Ԃ̂��ߒ���������
}


CameraControll::~CameraControll() {
}


// �ȉ��A�O������̐ݒ�p���\�b�h
void CameraControll::setWorld(const XMMATRIX& world) {
	m_world = world;
}
void CameraControll::setView(const XMVECTOR& eye, const XMVECTOR& at, const XMVECTOR& up) {
	m_view = XMMatrixLookAtLH(eye, at, up);
}

void CameraControll::setEye(const XMVECTOR& eye) {
	m_eye = eye;
}

void CameraControll::setAt(const XMVECTOR& at) {
	m_at = at;
}

void CameraControll::setUp(const XMVECTOR& up) {
	m_up = up;
}

void CameraControll::setProjection(const UINT width, const UINT height) {
	m_projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
}

DirectX::XMMATRIX CameraControll::getWorld() {
	return m_world;
}

DirectX::XMMATRIX CameraControll::getView() {
	// ���݂̒l��K�p�����čŐV�̂��̂ɂ���
	m_view = XMMatrixLookAtLH(m_eye, m_at, m_up);
	return m_view;
}

DirectX::XMVECTOR CameraControll::getEye() {
	return m_eye;
}

DirectX::XMVECTOR CameraControll::getAt() {
	return m_at;
}

DirectX::XMVECTOR CameraControll::getUp() {
	return m_up;
}

DirectX::XMMATRIX CameraControll::getProjection() {
	return m_projection;
}
