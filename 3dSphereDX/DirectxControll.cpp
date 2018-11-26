#include "DirectxControll.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;

HRESULT DirectxControll::InitDevice(HWND hwnd) {
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(hwnd, &rc);
	// ウィンドウのクライアント領域の幅・高さ取得
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	// Dx11.0の一時的なドライバ・コンテキスト・スワップチェイン格納用
	ComPtr<ID3D11Device> g_pd3dDevice = nullptr;
	ComPtr<ID3D11DeviceContext> g_pImmediateContext = nullptr;
	ComPtr<IDXGISwapChain> g_pSwapChain = nullptr;

	// ランタイムレイヤー設定。デバッグ用ならデバッグ設定になる
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// デバイスの機能レベル いま設定できるもので最新のもので設定
	D3D_FEATURE_LEVEL featureLevels[] =	{D3D_FEATURE_LEVEL_11_1};

	// Dx11.0のデバイスおよびコンテキスト作成
	D3D11CreateDevice(nullptr, g_driverType, nullptr, 
						   createDeviceFlags, featureLevels, 1,
						   D3D11_SDK_VERSION, &g_pd3dDevice, nullptr,
						   &g_pImmediateContext);

	if (FAILED(hr)) {
		return hr;
	}

	// Dx11.0のデバイス・コンテキストから、Dx11.1のデバイス・コンテキスト作成
	// チュートリアルとは違って、DXGIDevice1インターフェースを取得したいので、ここで各種作成を行う
	g_pd3dDevice.As(&g_pd3dDevice1);
	g_pImmediateContext.As(&g_pImmediateContext1);

	// 各種IDXG関連ファクトリー格納用
	ComPtr<IDXGIDevice1> dxgiDevice = nullptr; // チュートリアルと比べてこちらのほうがいいらしい
	ComPtr<IDXGIAdapter> adapter = nullptr;
	ComPtr<IDXGIFactory1> dxgiFactory = nullptr;
	ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;

	// デバイスから、各種IDXG関連を作成する
	hr = g_pd3dDevice1.As(&dxgiDevice);
	hr = dxgiDevice->GetAdapter(&adapter);
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), &dxgiFactory);
	hr = dxgiFactory.As(&dxgiFactory2);
	if (FAILED(hr)) {
		return hr;
	}

	// スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC1 sd = {};
	sd.Width = width;
	sd.Height = height;
	sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;

	// スワップチェインの作成(Dx11.1のため、CreateSwapChainメソッドではない)
	hr = dxgiFactory2->CreateSwapChainForHwnd(g_pd3dDevice.Get(), hwnd, &sd, 
											  nullptr, nullptr, &g_pSwapChain1);

	if (SUCCEEDED(hr)) {
		// Dx11.0のスワップチェインの取得
		hr = g_pSwapChain1.As(&g_pSwapChain);
	}

	if (FAILED(hr)) {
		return hr;
	}

	// レンダーターゲットビューを作成するためのバックバッファオブジェクトの作成
	ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	// レンダーターゲットビューを作成
	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &g_pRenderTargetView);
	if (FAILED(hr)) {
		return hr;
	}

	// 深度ステンシルバッファの作成
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = g_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);

	// 深度ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil.Get(), &descDSV, &g_pDepthStencilView);

	// コンテキストにレンダーターゲットビューと深度ステンシルビューをバインドする
	g_pImmediateContext->OMSetRenderTargets(1, g_pRenderTargetView.GetAddressOf(), g_pDepthStencilView.Get());

	// ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);

	// 初期化完了
	return S_OK;
}

DirectxControll::~DirectxControll() {

}

// コンテキストへのポインタを返す
ComPtr<ID3D11DeviceContext1> DirectxControll::GetContext() {
	return g_pImmediateContext1.Get();
}

// スワップチェインへのポインタを返す
ComPtr<IDXGISwapChain1> DirectxControll::GetSwapChain() {
	return g_pSwapChain1.Get();
}

// バックバッファの初期化
 void DirectxControll::ClearBackBuffer() {
	 g_pImmediateContext1->ClearRenderTargetView(g_pRenderTargetView.Get(), Colors::MidnightBlue);
}

// 深度バッファの初期化
void DirectxControll::ClearDepthBuffer() {
	g_pImmediateContext1->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}