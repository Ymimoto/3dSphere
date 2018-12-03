#include "stdafx.h"
#include "DrowSpheres.h"
#include "CameraControll.h"

using namespace std;
using namespace DirectX;
using Microsoft::WRL::ComPtr;

DrowSpheres::DrowSpheres() {
}


DrowSpheres::~DrowSpheres() {
}

void DrowSpheres::setSphere(ComPtr<ID3D11DeviceContext1> &context) {
	random_device device;
	mt19937 mt(device());
	// �����_���o�������̂ŁA�擾���ʂ�1000�Ŋ���O��(100�Ŋ���Ƃ�����Ƒ傫������)
	uniform_int_distribution<> distX(-1000, 999);
	uniform_int_distribution<> distY(-500, 499);
	uniform_int_distribution<> distZ(0, 200);
	uniform_int_distribution<> distR(0, 100);
	uniform_int_distribution<> distG(0, 100);
	uniform_int_distribution<> distB(0, 100);
	uniform_int_distribution<> distRa(500, 1500);
	for (int i = 0; i < constParam::SPHERENUM; i++) {
		p_sphere[i] = make_unique<SphereSet>();
		p_sphere[i]->centerPos = XMFLOAT3((float)distX(mt)/100, (float)distY(mt) / 100, (float)distZ(mt) / 100);
		p_sphere[i]->bodyColor = XMFLOAT4((float)distR(mt) / 100, (float)distG(mt) / 100, (float)distB(mt) / 100, 1.0f);
		p_sphere[i]->radius = (float)distRa(mt) / 1000;
		p_sphere[i]->sphere = GeometricPrimitive::CreateSphere(context.Get(), p_sphere[i]->radius * 2, 24, false, false);
	}
}

void DrowSpheres::drow(const shared_ptr<CameraControll>& camera) {
	// ���ۂ͈����̏������ƂɁA�����_�����O���Ƀ\�[�g��������
	// (�����0,0,0���瓮�����Ȃ��̂Ń����_�����O�O�̒l�Ń\�[�g��������
	// �\�[�g�����A���[���h���W�����[�J�����W�ɕϊ������Ă���A�ԊҌ��Z���Ń\�[�g
	// �����������Ƃ��͕��񏈗����l����B
	sort(p_sphere.begin(), p_sphere.end(), [](const unique_ptr<SphereSet>& left, const unique_ptr<SphereSet>& right) {
		return left->centerPos.z < right->centerPos.z;
	});
	// FXMVECTOR�^��4���̈������킽��
	for (int i = 0; i < constParam::SPHERENUM; i++) {
		XMMATRIX position = XMMatrixMultiply(camera->getWorld(), XMMatrixTranslation(p_sphere[i]->centerPos.x, p_sphere[i]->centerPos.y, p_sphere[i]->centerPos.z));
		XMVECTORF32 color = {p_sphere[i]->bodyColor.x,p_sphere[i]->bodyColor.y,p_sphere[i]->bodyColor.z,p_sphere[i]->bodyColor.w};
		p_sphere[i]->sphere->Draw(position, camera->getView(), camera->getProjection(), color);
	}
}
