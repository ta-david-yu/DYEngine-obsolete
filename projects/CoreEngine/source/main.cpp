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

	printf("test passed!");

	SYSTEM_MGR->Awake();
	SYSTEM_MGR->Start();

	while (1)
	{
		SYSTEM_MGR->Update();
		SYSTEM_MGR->LateUpdate();
		SYSTEM_MGR->FixedUpdate();
	}
}

int main()
{
	test();
	system("PAUSE");
	return 0;
}
