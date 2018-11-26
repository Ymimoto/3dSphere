#pragma once
class DirectxControll;
class CameraControll;
class TimerControll;
class DrowSpheres;

// �s����Agamemanager�Ƃ������O�ɂ��Ă��邯�ǁA
// �������[�g�̃}�l�[�W��
class GameManager {
private:
	// �V�X�e���n�̃|�C���^
	std::unique_ptr<DirectxControll> dxInstance = nullptr;
	std::shared_ptr<CameraControll> camera = nullptr;
	std::unique_ptr<TimerControll> timerInstance = nullptr;

	// �R���g���[���n�̃|�C���^
	std::unique_ptr<DrowSpheres> drSphere = nullptr;

public:
	// �󂯎�葤��unique_ptr�łƂ邱�ƁI
	GameManager(HWND hwnd);
	~GameManager();

	// ���������\�b�h
	void Loop();
};



