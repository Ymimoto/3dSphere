#include "windowMain.h"

windowMain::windowMain() {
}


windowMain::~windowMain() {
}

// ウィンドウハンドラを返すgetter
HWND windowMain::getHwnd() {
	return g_hWnd;
}

// ウィンドウの作成
HRESULT windowMain::InitWindow(HINSTANCE hInstance, int nCmdShow, WCHAR* titleName, WCHAR* WindowClassName, UINT width, UINT height) {

	wcscpy_s(szWindowClass, WindowClassName);
	wcscpy_s(szTitle, titleName);

	// ウィンドウクラスを作成
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = windowMain::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DSPHEREDX));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WindowClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (!RegisterClassEx(&wcex)) {
		return E_FAIL;
	}

	// インスタンス格納
	hInst = hInstance;
	// ウィンドウサイズの計算
	auto rc = RECT{0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウ作成
	g_hWnd = CreateWindow(szWindowClass, szWindowClass,
						  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
						  CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
						  nullptr, nullptr, hInstance, nullptr);
	if (!g_hWnd) {
		return E_FAIL;
	}

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

// ウィンドウプロシージャ
LRESULT windowMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
