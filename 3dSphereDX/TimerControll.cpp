// http://marupeke296.com/DXCLSSmp_FPSCounter.html
// こちらをすっきりカスタマイズしたもの

#include "TimerControll.h"

// コンストラクタ
TimerControll::TimerControll() {
	// サンプル数の設定
	m_uiNum = SampleNum::uiNum;    // 平均を計算する個数
	m_dwDefTimeLst.resize(SampleNum::uiNum, 0.0);    // リスト初期化
	m_dwSumTimes = 0;

	// 計測する時計の選択
	QueryPerformanceCounter(&m_Counter); // 現在の時間を取得
	m_PrevCounter = m_Counter;           // 前回の時間を現在の時間と同値に初期化
	QueryPerformanceFrequency(&m_Freq);  // 現在の周波数を取得

	// 計測
	GetFPS();
}

// デストラクタ
TimerControll::~TimerControll(void) {
}


// FPS値を取得
double TimerControll::GetFPS() {
	double Def = GetCurDefTime();
	if (Def == 0) {
		// 計算できないのでを返す
		return 0;
	}

	return UpdateFPS(Def);
}


// 現在の差分時刻をミリ秒単位で取得
double TimerControll::GetCurDefTime() {
	// 差分時間を計測
	QueryPerformanceCounter(&m_Counter);                                        // 現在の時刻を取得
	double dDef = (double)m_Counter.QuadPart - (double)m_PrevCounter.QuadPart;  // 前回取得時との差分を算出
	m_PrevCounter = m_Counter;                                                  // 現在の時刻を保持
	return dDef * 1000 / (double)m_Freq.QuadPart;                               // 差分時間をミリ秒単位で返す
}


// FPSを更新
double TimerControll::UpdateFPS(double Def) {
	// 最も古いデータを消去
	m_dwDefTimeLst.pop_front();

	// 新しいデータを追加
	m_dwDefTimeLst.push_back(Def);

	// FPS算出
	double FPS = 0.0f;
	double AveDef = (m_dwSumTimes + Def) / m_uiNum;
	if (AveDef != 0) {
		FPS = 1000.0 / AveDef;
	}

	// 共通加算部分の更新
	m_dwSumTimes += Def - *m_dwDefTimeLst.begin();

	return FPS;
}
