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

	printf("test passed!\n");

	SYSTEM_MGR->Awake();
	SYSTEM_MGR->Start();

	Transform* trans = ent00->GetTransform();
	trans->SetPosition(Vector3f(0, 1876, 0));
	Vector3f pos = trans->GetPosition();
	printf("POS: %f %f %f\n", pos.x(), pos.y(), pos.z());

	/*
	Resource<int>* intRrc = static_cast<Resource<int>*>(RESOURCE_MGR->Load<int>("", 0, nullptr));
	int* IntPtr = intRrc->GetValue();
	assert((*IntPtr) == 0);
	(*IntPtr) = 20;
	assert((*IntPtr) == 20);
	assert( *intRrc->GetValue() == 20);
	*/
	Resource<Mesh>* RMesh = RESOURCE_MGR->Load<Mesh>("", 0, nullptr);
	Mesh* mesh = RMesh->GetValue();
	
	std::size_t  size = sizeof(Vector3f);
	printf("%d\n", size);
	
	
/*
	while (1)
	{
		SYSTEM_MGR->Update();
		SYSTEM_MGR->LateUpdate();
		SYSTEM_MGR->FixedUpdate();
	}*/
}

int main()
{
	test();
	system("PAUSE");
	return 0;
}
