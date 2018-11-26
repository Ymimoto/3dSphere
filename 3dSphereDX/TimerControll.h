// http://marupeke296.com/DXCLSSmp_FPSCounter.html
// こちらをすっきりカスタマイズしたもの

#pragma once
#include <mmsystem.h>
#include <list>

using namespace std;

enum SampleNum { uiNum = 10 }; // 平均計算時のデータ数

class TimerControll {
private:
	LARGE_INTEGER m_Counter;           // クロックカウント数
	LARGE_INTEGER m_Freq;			   // 周波数
	LARGE_INTEGER m_PrevCounter;       // 以前のクロックカウント数
	LONGLONG m_OldLongCount;           // 以前のクロックカウント数
	DWORD m_dwTGTOldCount;             // 以前の時刻（ミリ秒）
	list<double> m_dwDefTimeLst;       // 時間リスト
	uint64_t m_uiNum;                  // 移動平均計算時のデータ数
	double m_dwSumTimes;               // 共通部分の合計値

public:
	TimerControll();
	virtual ~TimerControll(void);

	// FPS値を取得
	double GetFPS();

protected:
	// 現在の時刻を取得
	double GetCurDefTime();

	// FPSを更新
	double UpdateFPS(double Def);
};