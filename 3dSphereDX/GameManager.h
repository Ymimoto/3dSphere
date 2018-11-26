#pragma once
class DirectxControll;
class CameraControll;
class TimerControll;
class DrowSpheres;

// 都合上、gamemanagerという名前にしているけど、
// 実質ルートのマネージャ
class GameManager {
private:
	// システム系のポインタ
	std::unique_ptr<DirectxControll> dxInstance = nullptr;
	std::shared_ptr<CameraControll> camera = nullptr;
	std::unique_ptr<TimerControll> timerInstance = nullptr;

	// コントローラ系のポインタ
	std::unique_ptr<DrowSpheres> drSphere = nullptr;

public:
	// 受け取り側はunique_ptrでとること！
	GameManager(HWND hwnd);
	~GameManager();

	// 実処理メソッド
	void Loop();
};



