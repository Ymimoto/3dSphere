#pragma once
class Sphere;
class CameraControll;

struct constParam {
	static const int SPHERENUM = 10;
};

// �ʂ̃w�b�_�t�@�C���ɂ܂Ƃ߂悤���Ǝv�������ǁA����قǂł��Ȃ��̂ł����ŋL��
struct SphereSet {
	DirectX::XMFLOAT3 centerPos;
	DirectX::XMFLOAT4 bodyColor;
	float radius;
	std::unique_ptr<DirectX::GeometricPrimitive> sphere;
};

class DrowSpheres {
private:
	std::array<std::unique_ptr<SphereSet>, 10> p_sphere;

public:
	DrowSpheres();
	~DrowSpheres();
	void setSphere(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &context);
	void drow(const std::shared_ptr<CameraControll>& camera);
};

