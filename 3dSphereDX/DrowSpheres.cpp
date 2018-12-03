#include "stdafx.h"
#include "DrowSpheres.h"
#include "CameraControll.h"

using namespace std;
using namespace DirectX;
using Microsoft::WRL::ComPtr;

DrowSpheres::DrowSpheres() {
}


DrowSpheres::~DrowSpheres() {
}

void DrowSpheres::setSphere(ComPtr<ID3D11DeviceContext1> &context) {
	random_device device;
	mt19937 mt(device());
	// 小数点を出したいので、取得結果を1000で割る前提(100で割るとちょっと大きすぎる)
	uniform_int_distribution<> distX(-1000, 999);
	uniform_int_distribution<> distY(-500, 499);
	uniform_int_distribution<> distZ(0, 200);
	uniform_int_distribution<> distR(0, 100);
	uniform_int_distribution<> distG(0, 100);
	uniform_int_distribution<> distB(0, 100);
	uniform_int_distribution<> distRa(500, 1500);
	for (int i = 0; i < constParam::SPHERENUM; i++) {
		p_sphere[i] = make_unique<SphereSet>();
		p_sphere[i]->centerPos = XMFLOAT3((float)distX(mt)/100, (float)distY(mt) / 100, (float)distZ(mt) / 100);
		p_sphere[i]->bodyColor = XMFLOAT4((float)distR(mt) / 100, (float)distG(mt) / 100, (float)distB(mt) / 100, 1.0f);
		p_sphere[i]->radius = (float)distRa(mt) / 1000;
		p_sphere[i]->sphere = GeometricPrimitive::CreateSphere(context.Get(), p_sphere[i]->radius * 2, 24, false, false);
	}
}

void DrowSpheres::drow(const shared_ptr<CameraControll>& camera) {
	// 実際は引数の情報をもとに、レンダリング順にソートをかける
	// (今回は0,0,0から動かさないのでレンダリング前の値でソートをかける
	// ソート条件、ワールド座標→ローカル座標に変換かけてから、返還後のZ軸でソート
	// 数が増えたときは並列処理も考える。
	sort(p_sphere.begin(), p_sphere.end(), [](const unique_ptr<SphereSet>& left, const unique_ptr<SphereSet>& right) {
		return left->centerPos.z < right->centerPos.z;
	});
	// FXMVECTOR型で4つけの引数をわたす
	for (int i = 0; i < constParam::SPHERENUM; i++) {
		XMMATRIX position = XMMatrixMultiply(camera->getWorld(), XMMatrixTranslation(p_sphere[i]->centerPos.x, p_sphere[i]->centerPos.y, p_sphere[i]->centerPos.z));
		XMVECTORF32 color = {p_sphere[i]->bodyColor.x,p_sphere[i]->bodyColor.y,p_sphere[i]->bodyColor.z,p_sphere[i]->bodyColor.w};
		p_sphere[i]->sphere->Draw(position, camera->getView(), camera->getProjection(), color);
	}
}
