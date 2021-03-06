// プリコンパイルヘッダはVSの設定で自動インクルードしています

#include "windowMain.h"
#include "DirectxControll.h"
#include "GameManager.h"
#include "3dSphereDX.h"

// directxmathを使うため
using namespace DirectX;
using namespace std;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){

	WCHAR szTitle[100] = {0};
	WCHAR szWindowClass[100] = {0};
	wcscpy_s(szTitle, TITLE_NAME);
	wcscpy_s(szWindowClass, WINDOW_CLASS_NAME);

	// ウィンドウの作成
	auto WMain = new windowMain();
	if (FAILED(WMain->InitWindow(hInstance, nCmdShow, szTitle, szWindowClass, windowSize::width, windowSize::height))) {
		return 0;
	}

	// ルートのマネージャを作成
	// 呼び出しは明らかにここだけのため、シングルトンにしない
	auto hwnd = WMain->getHwnd();
	iGameManager = make_unique<GameManager>(hwnd);

	// メイン メッセージ ループ
	Loop();

    return 0;
}

// メッセージループ
void Loop() {
	MSG msg = {0};
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			Process();
		}
	}
}

void Process() {
	// 以下処理をかいてね 
	iGameManager->Loop();
}


