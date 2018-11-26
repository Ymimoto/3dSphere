#pragma once

class CameraControll {

private:
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;

	DirectX::XMVECTOR m_eye;
	DirectX::XMVECTOR m_at;
	DirectX::XMVECTOR m_up;
public:
	CameraControll();
	~CameraControll();
	DirectX::XMMATRIX getWorld();
	DirectX::XMMATRIX getView();
	DirectX::XMVECTOR getEye();
	DirectX::XMVECTOR getAt();
	DirectX::XMVECTOR getUp();
	DirectX::XMMATRIX getProjection();
	void setWorld(const DirectX::XMMATRIX& world);
	void setView(const DirectX::XMVECTOR& eye, const DirectX::XMVECTOR& at, const DirectX::XMVECTOR& up);
	void setEye(const DirectX::XMVECTOR& eye);
	void setAt(const DirectX::XMVECTOR& at);
	void setUp(const DirectX::XMVECTOR& up);
	void setProjection(const UINT width, const UINT height);
};

