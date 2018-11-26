// http://marupeke296.com/DXCLSSmp_FPSCounter.html
// ���������������J�X�^�}�C�Y��������

#pragma once
#include <mmsystem.h>
#include <list>

using namespace std;

enum SampleNum { uiNum = 10 }; // ���όv�Z���̃f�[�^��

class TimerControll {
private:
	LARGE_INTEGER m_Counter;           // �N���b�N�J�E���g��
	LARGE_INTEGER m_Freq;			   // ���g��
	LARGE_INTEGER m_PrevCounter;       // �ȑO�̃N���b�N�J�E���g��
	LONGLONG m_OldLongCount;           // �ȑO�̃N���b�N�J�E���g��
	DWORD m_dwTGTOldCount;             // �ȑO�̎����i�~���b�j
	list<double> m_dwDefTimeLst;       // ���ԃ��X�g
	uint64_t m_uiNum;                  // �ړ����όv�Z���̃f�[�^��
	double m_dwSumTimes;               // ���ʕ����̍��v�l

public:
	TimerControll();
	virtual ~TimerControll(void);

	// FPS�l���擾
	double GetFPS();

protected:
	// ���݂̎������擾
	double GetCurDefTime();

	// FPS���X�V
	double UpdateFPS(double Def);
};