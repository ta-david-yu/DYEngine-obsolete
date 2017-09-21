#include <DYEngine\Main.h>

#include <iostream>

using namespace DYE;

int main()
{
	Scene* scene00 = new Scene();
	Entity* ent00 = scene00->CreateEntity("Obj00");
	IComponent* comp00 = ent00->AddComponent<ReusablePool>();
	ReusablePool* pool = dynamic_cast<ReusablePool*>(comp00);
	pool->Init();

	if (SYSTEM_MGR->HasSystem<Transform>())
		printf("HAS TRANS\n");
	else
		printf("NO TRANS\n");

	if (SYSTEM_MGR->HasSystem<DummyComponent>())
		printf("HAS TRANS\n");
	else
		printf("NO TRANS\n");

	if (comp00->GetComponent<Transform>() != nullptr)
		printf("HAS TRANS\n");
	else
		printf("NO TRANS\n");
	
	std::cout << comp00->GetTransform()->GetName() << std::endl;

	if (ent00->GetTransform() != comp00->GetTransform())
		printf("is not equal\n");
	else
		printf("is equal\n");

	system("PAUSE");
	return 0;
}
