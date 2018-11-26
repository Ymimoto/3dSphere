
# include <Siv3D.hpp>
#include <memory>
#include <array>

struct SphereSet {
public:
	Vec3 centerPos;
	Color bodyColor;
	double radius;
	//Sphere drowSphere;
};
using namespace std;
#define SPHERENUM 10

void Main()
{
	//auto SphereData = make_unique<array<SphereSet, SPHERENUM>>();
	array <unique_ptr<SphereSet>, SPHERENUM> SphereData;

	for (int i = 0; i < SPHERENUM; i++) {
	//for (auto set : SphereData) {
		SphereData[i] = make_unique<SphereSet>();
		SphereData[i]->centerPos = Vec3(Random(-10.0, 10.0), Random(-5.0, 5.0), Random(0.0, 2.0));
		SphereData[i]->bodyColor = Color(Random(0, 255), Random(0, 255), Random(0, 255));
		SphereData[i]->radius = Random(1.0, 3.0);
	}

	while (System::Update())
	{
		Graphics3D::FreeCamera();
		for (int i = 0; i < SPHERENUM; i++) {
			Sphere(SphereData[i]->centerPos, SphereData[i]->radius).draw(SphereData[i]->bodyColor);
		}
	}
}
