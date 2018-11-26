#pragma once
#include "Resource.h"

class DirectxControll;

#define TITLE_NAME L"作成テスト"
#define WINDOW_CLASS_NAME L"作成テスト"

// プロトタイプ宣言
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void                Loop();
void                Process();

// 変数宣言
std::unique_ptr<GameManager> iGameManager;

