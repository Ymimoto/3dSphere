#pragma once
#include "resource.h"

class windowMain {
	// タイトルバー・メインウィンドウクラス名の最大文字数
#define MAX_LOADSTRING 100
private : 
	// 現在のインターフェイス
	HINSTANCE hInst = nullptr;
	// ウィンドウハンドラ
	HWND g_hWnd = nullptr;

	const int max_LoadString = 100;
	// タイトル バーのテキスト
	WCHAR szTitle[MAX_LOADSTRING];
	// メイン ウィンドウ クラス名
	WCHAR szWindowClass[MAX_LOADSTRING];

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	windowMain();
	~windowMain();
	HWND getHwnd();
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow,WCHAR* titleName, WCHAR* WindowClassName, UINT width, UINT height);
	
};

