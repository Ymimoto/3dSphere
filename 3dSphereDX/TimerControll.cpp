// http://marupeke296.com/DXCLSSmp_FPSCounter.html
// ���������������J�X�^�}�C�Y��������

#include "TimerControll.h"

// �R���X�g���N�^
TimerControll::TimerControll() {
	// �T���v�����̐ݒ�
	m_uiNum = SampleNum::uiNum;    // ���ς��v�Z�����
	m_dwDefTimeLst.resize(SampleNum::uiNum, 0.0);    // ���X�g������
	m_dwSumTimes = 0;

	// �v�����鎞�v�̑I��
	QueryPerformanceCounter(&m_Counter); // ���݂̎��Ԃ��擾
	m_PrevCounter = m_Counter;           // �O��̎��Ԃ����݂̎��ԂƓ��l�ɏ�����
	QueryPerformanceFrequency(&m_Freq);  // ���݂̎��g�����擾

	// �v��
	GetFPS();
}

// �f�X�g���N�^
TimerControll::~TimerControll(void) {
}


// FPS�l���擾
double TimerControll::GetFPS() {
	double Def = GetCurDefTime();
	if (Def == 0) {
		// �v�Z�ł��Ȃ��̂ł�Ԃ�
		return 0;
	}

	return UpdateFPS(Def);
}


// ���݂̍����������~���b�P�ʂŎ擾
double TimerControll::GetCurDefTime() {
	// �������Ԃ��v��
	QueryPerformanceCounter(&m_Counter);                                        // ���݂̎������擾
	double dDef = (double)m_Counter.QuadPart - (double)m_PrevCounter.QuadPart;  // �O��擾���Ƃ̍������Z�o
	m_PrevCounter = m_Counter;                                                  // ���݂̎�����ێ�
	return dDef * 1000 / (double)m_Freq.QuadPart;                               // �������Ԃ��~���b�P�ʂŕԂ�
}


// FPS���X�V
double TimerControll::UpdateFPS(double Def) {
	// �ł��Â��f�[�^������
	m_dwDefTimeLst.pop_front();

	// �V�����f�[�^��ǉ�
	m_dwDefTimeLst.push_back(Def);

	// FPS�Z�o
	double FPS = 0.0f;
	double AveDef = (m_dwSumTimes + Def) / m_uiNum;
	if (AveDef != 0) {
		FPS = 1000.0 / AveDef;
	}

	// ���ʉ��Z�����̍X�V
	m_dwSumTimes += Def - *m_dwDefTimeLst.begin();

	return FPS;
}
