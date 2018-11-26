#include "stdafx.h"
#include "GameManager.h"
#include "DirectxControll.h"
#include "CameraControll.h"
#include "TimerControll.h"
#include "DrowSpheres.h"


using namespace std;

// directxmathを使うため
using namespace DirectX;

GameManager::GameManager(HWND hwnd) {
	// 各種デバイスの初期化
	dxInstance = make_unique<DirectxControll>();
	dxInstance->InitDevice(hwnd);

	// カメラの設定
	// 書く描画の際に現在の情報を渡すため、unique_ptrではなくshared_ptrで管理
	// camera = make_shared<CameraControll>(nullptr);
	// メモ:現環境でmake_shared<>()を使うと、システム的な都合で死ぬので、以下の感じで使うといい。
	camera.reset(new CameraControll());

	// タイマーセット
	timerInstance = make_unique<TimerControll>();

}

GameManager::~GameManager() {
}

void GameManager::Loop() {
	// 各種オブジェクトの初期化
	// タイマー処理
	timerInstance->GetFPS();

	// 実際は
	//
	// コア┬シーン┬マネージャ┬キャラクタ等の管理マネージャ┬そのオブジェクトのコントローラ┬モデル
	//　　 └     └       　└                       └　　　　　　　　　　　　　　 └ビュー
	// なかんじのECSチックな構造にしたいけど。一部は作ってもシンプルなものになってしまうので、そのへんはこのマネージャに集約させる
	// 現段階は、コアとシーンは管理マネージャと一緒にする
	// つまり
	// コア～マネージャがここ
	// オブジェクトのコントローラがDrowSpheres
	// モデルはカメラがCameraComponent
	//        位置情報がTransformComponent
	//        オブジェクトの情報がObjectComponent


	// directX関連取得(本来はコアのほうで呼ぶ想定)
	static ComPtr<ID3D11DeviceContext1> context = dxInstance->GetContext();
	static ComPtr<IDXGISwapChain1> swapChain = dxInstance->GetSwapChain();
	
	// カメラの設定
	camera->setEye(XMVectorSet(0.0f, 3.0f, -16.0f, 0.0f));
	camera->setAt(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	camera->setProjection(windowSize::width, windowSize::height);
	// CBNeverChangesやCBChangeOnResizeは必要に応じて作ろう

	// 本来なら BackgroundManagerとかCharacterManagerとか作ってそこで制御するのだろう
	if (drSphere == nullptr) {
		// 呼び出しは明らかにここだけのため、シングルトンにしない
		drSphere = make_unique<DrowSpheres>();

		// 表示するものを設定
		drSphere->setSphere(context);
	}

	// 時間の更新(今回はやらない)

	// 描画初期化
	dxInstance->ClearBackBuffer();
	dxInstance->ClearDepthBuffer();

	// 描画処理(といっても今回はdirectXTK使うので、別途directXの描画用クラスを定義をしないで
	// drSphere内で使用しているdirectXTKの描画をたたくのみ)
	drSphere->drow(camera);

	swapChain->Present(0, 0);
}