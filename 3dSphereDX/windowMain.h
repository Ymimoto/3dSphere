#pragma once
#include "resource.h"

class windowMain {
	// �^�C�g���o�[�E���C���E�B���h�E�N���X���̍ő啶����
#define MAX_LOADSTRING 100
private : 
	// ���݂̃C���^�[�t�F�C�X
	HINSTANCE hInst = nullptr;
	// �E�B���h�E�n���h��
	HWND g_hWnd = nullptr;

	const int max_LoadString = 100;
	// �^�C�g�� �o�[�̃e�L�X�g
	WCHAR szTitle[MAX_LOADSTRING];
	// ���C�� �E�B���h�E �N���X��
	WCHAR szWindowClass[MAX_LOADSTRING];

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	windowMain();
	~windowMain();
	HWND getHwnd();
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow,WCHAR* titleName, WCHAR* WindowClassName, UINT width, UINT height);
	
};

