#include <DYEngine\Main.h>

#include <iostream>
#include <cassert>

using namespace DYE;

void test()
{
	Scene* scene00 = new Scene();
	Entity* ent00 = scene00->CreateEntity();
	IComponent* comp00 = ent00->AddComponent<ReusablePool>();
	ReusablePool* pool = dynamic_cast<ReusablePool*>(comp00);
	pool->Init();

	assert(SYSTEM_MGR->HasSystem<ReusablePool>());

	assert(SYSTEM_MGR->HasSystem<Transform>());

	assert(comp00->GetComponent<Transform>() == comp00->GetTransform());

	assert(!SYSTEM_MGR->HasSystem<DummyComponent>());

	ent00->SetName("Obj00_v1");
	assert(comp00->GetName() == "Obj00_v1");
	assert(ent00->GetName() == "Obj00_v1");

	comp00->SetName("Obj00_v2");
	assert(comp00->GetName() == "Obj00_v2");
	assert(ent00->GetName() == "Obj00_v2");

	ent00->SetName("Obj00_v3");
	assert(comp00->GetName() == "Obj00_v3");
	assert(ent00->GetName() == "Obj00_v3");

	comp00->SetName("Obj00_v4");
	assert(comp00->GetName() == "Obj00_v4");
	assert(ent00->GetName() == "Obj00_v4");

	Vector3f unitX = Vector3f::UnitX();
	Vector3f unitY = Vector3f::UnitY();

	Vector3f normX = unitX.Normalized();
	Vector3f normY = unitY.Normalized();

	Vector3f x(1, 0, 0);
	Vector3f y(0, 1, 0);

	float value = 25;
	Vector3f bigX(value, 0, 0);
	Vector3f bigY(0, value, 0);
	Vector3f bigXY(value, value, 0);

	assert(unitX == normX);
	assert(unitY == normY);
	assert(x == normX);
	assert(y == normY);
	assert(unitX != normY);
	assert(unitY != normX);
	assert(x != normY);
	assert(y != normX);
	assert(x == bigX.Normalized());
	assert(y == bigY.Normalized());

	assert(Math::IsEqual(bigX.Magnitude(), bigY.Magnitude()));
	assert(bigXY == (bigX + bigY));

	Vector2f x2 = Vector2f::UnitX();
	Vector2f x2_0 = Vector2f::UnitX();
	assert(x2 == x2_0);

	printf("test passed!\n");

	SYSTEM_MGR->Awake();
	SYSTEM_MGR->Start();

	Transform* trans = ent00->GetTransform();
	trans->SetPosition(Vector3f(0, 1876, 0));
	Vector3f pos = trans->GetPosition();
	printf("POS: %f %f %f\n", pos.x(), pos.y(), pos.z());

	Resource<Mesh>* RMesh = RESOURCE_MGR->Load<Mesh>("", 0, nullptr);
	Mesh* mesh = RMesh->GetValue();
	
	std::size_t  size = sizeof(Vector3f);
	printf("Vector3 Size: %d\n", size);
}

int main()
{
	test();
	system("PAUSE");
	return 0;
}
