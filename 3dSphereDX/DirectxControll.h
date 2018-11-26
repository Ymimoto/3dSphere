#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#pragma comment (lib, "d3d11.lib")

using Microsoft::WRL::ComPtr;

class DirectxControll {
private:
	// å¥ë•ÅADx11.1Çégóp
	D3D_DRIVER_TYPE                g_driverType = D3D_DRIVER_TYPE_HARDWARE;
	D3D_FEATURE_LEVEL              g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ComPtr<ID3D11Device1>          g_pd3dDevice1 = nullptr;
	ComPtr<ID3D11DeviceContext1>   g_pImmediateContext1 = nullptr;
	ComPtr<IDXGISwapChain1>        g_pSwapChain1 = nullptr;
	ComPtr<ID3D11RenderTargetView> g_pRenderTargetView = nullptr;
	ComPtr<ID3D11Texture2D>        g_pDepthStencil = nullptr;
	ComPtr<ID3D11DepthStencilView> g_pDepthStencilView = nullptr;

public:
	~DirectxControll();
	HRESULT InitDevice(HWND hwnd);
	ComPtr<ID3D11DeviceContext1> GetContext();
	ComPtr<IDXGISwapChain1> GetSwapChain();
	void ClearBackBuffer();
	void ClearDepthBuffer();
};

