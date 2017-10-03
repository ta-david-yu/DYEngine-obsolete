#include <DYEngine\Main.h>

#include <iostream>
#include <cassert>

using namespace DYE;

void testMathType()
{
	//-------------Test Math Type-------------//
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

	Vector3f forward = Vector3f::UnitZ();
	Vector3f right = Vector3f::UnitX();
	Quaternion fToR = Quaternion(Vector3f(0, 90, 0));

	Vector3f rotRight = fToR * forward;

	printf("ori: %s\n", right.ToString());
	printf("rot: %s\n", rotRight.ToString());
	assert(rotRight == right);

	printf("test passed!\n");
}

void testSceneOperation()
{
	//-------------Test Scene Operation-------------//
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

	SYSTEM_MGR->Awake();
	SYSTEM_MGR->Start();

	printf("test passed!\n");
}

void testResource()
{
	Resource<Mesh>* RMesh = RESOURCE_MGR->Load<Mesh>("", 0, nullptr);
	Mesh* mesh = RMesh->GetValue();

	printf("test passed!\n");
}

void testInstantiate()
{
	Scene* scene = new Scene();

	//-------------Test Entity Instantiate Operation-------------//
	{
		// prototype
		Entity* root = scene->CreateEntity("Root");
		root->GetTransform()->SetPosition(Vector3f(0, 0, 0));
		root->GetTransform()->SetLocalScale(Vector3f(0, 0, 0));

		Entity* ent0 = scene->CreateEntity("Nod0");
		ent0->GetTransform()->SetParent(root->GetTransform());
		ent0->GetTransform()->SetPosition(Vector3f(1, 1, 1));
		ent0->GetTransform()->SetLocalScale(Vector3f(0, 90, 0));

		ent0->SetActive(false);
		/*
		Entity* ent1 = scene->CreateEntity("Nod1");
		ent1->GetTransform()->SetParent(ent0->GetTransform());
		ent1->GetTransform()->SetPosition(Vector3f(2, 2, 2));
		ent1->GetTransform()->SetScale(Vector3f(0, 180, 0));
		*/
		// clone
		Entity* cEnt[4];

		for (int i = 0; i < 4; i++)
		{
			cEnt[i] = dynamic_cast<Entity*>(Base::Instantiate(root));
			cEnt[i]->GetTransform()->SetParent(ent0->GetTransform());
		}

		cEnt[2]->GetTransform()->SetParent(cEnt[3]->GetTransform());

		printf("%s\n", root->ToString());

		SYSTEM_MGR->EarlyUpdate();

		printf("\n%s\n", root->ToString());
		

	}
}

int main()
{
	testMathType();
	testSceneOperation();
	testResource();
	testInstantiate();

	system("PAUSE");
	return 0;
}
