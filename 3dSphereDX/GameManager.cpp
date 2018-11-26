#include "stdafx.h"
#include "GameManager.h"
#include "DirectxControll.h"
#include "CameraControll.h"
#include "TimerControll.h"
#include "DrowSpheres.h"


using namespace std;

// directxmath���g������
using namespace DirectX;

GameManager::GameManager(HWND hwnd) {
	// �e��f�o�C�X�̏�����
	dxInstance = make_unique<DirectxControll>();
	dxInstance->InitDevice(hwnd);

	// �J�����̐ݒ�
	// �����`��̍ۂɌ��݂̏���n�����߁Aunique_ptr�ł͂Ȃ�shared_ptr�ŊǗ�
	// camera = make_shared<CameraControll>(nullptr);
	// ����:������make_shared<>()���g���ƁA�V�X�e���I�ȓs���Ŏ��ʂ̂ŁA�ȉ��̊����Ŏg���Ƃ����B
	camera.reset(new CameraControll());

	// �^�C�}�[�Z�b�g
	timerInstance = make_unique<TimerControll>();

}

GameManager::~GameManager() {
}

void GameManager::Loop() {
	// �e��I�u�W�F�N�g�̏�����
	// �^�C�}�[����
	timerInstance->GetFPS();

	// ���ۂ�
	//
	// �R�A���V�[�����}�l�[�W�����L�����N�^���̊Ǘ��}�l�[�W�������̃I�u�W�F�N�g�̃R���g���[�������f��
	//�@�@ ��     ��       �@��                       ���@�@�@�@�@�@�@�@�@�@�@�@�@�@ ���r���[
	// �Ȃ��񂶂�ECS�`�b�N�ȍ\���ɂ��������ǁB�ꕔ�͍���Ă��V���v���Ȃ��̂ɂȂ��Ă��܂��̂ŁA���̂ւ�͂��̃}�l�[�W���ɏW�񂳂���
	// ���i�K�́A�R�A�ƃV�[���͊Ǘ��}�l�[�W���ƈꏏ�ɂ���
	// �܂�
	// �R�A�`�}�l�[�W��������
	// �I�u�W�F�N�g�̃R���g���[����DrowSpheres
	// ���f���̓J������CameraComponent
	//        �ʒu���TransformComponent
	//        �I�u�W�F�N�g�̏��ObjectComponent


	// directX�֘A�擾(�{���̓R�A�̂ق��ŌĂԑz��)
	static ComPtr<ID3D11DeviceContext1> context = dxInstance->GetContext();
	static ComPtr<IDXGISwapChain1> swapChain = dxInstance->GetSwapChain();
	
	// �J�����̐ݒ�
	camera->setEye(XMVectorSet(0.0f, 3.0f, -16.0f, 0.0f));
	camera->setAt(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	camera->setProjection(windowSize::width, windowSize::height);
	// CBNeverChanges��CBChangeOnResize�͕K�v�ɉ����č�낤

	// �{���Ȃ� BackgroundManager�Ƃ�CharacterManager�Ƃ�����Ă����Ő��䂷��̂��낤
	if (drSphere == nullptr) {
		// �Ăяo���͖��炩�ɂ��������̂��߁A�V���O���g���ɂ��Ȃ�
		drSphere = make_unique<DrowSpheres>();

		// �\��������̂�ݒ�
		drSphere->setSphere(context);
	}

	// ���Ԃ̍X�V(����͂��Ȃ�)

	// �`�揉����
	dxInstance->ClearBackBuffer();
	dxInstance->ClearDepthBuffer();

	// �`�揈��(�Ƃ����Ă������directXTK�g���̂ŁA�ʓrdirectX�̕`��p�N���X���`�����Ȃ���
	// drSphere���Ŏg�p���Ă���directXTK�̕`����������̂�)
	drSphere->drow(camera);

	swapChain->Present(0, 0);
}