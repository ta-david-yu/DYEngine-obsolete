#include <DYEngine\Main.h>

#include <iostream>

using namespace DYE;

int main()
{
	IEntity ent;
	IComponent* comp = ent.AddComponent<DummyComponent>();

	if (SYSTEM_MGR->HasSystem<Transform>())
		printf("HAS TRANS\n");
	else
		printf("NO TRANS\n");

	if (SYSTEM_MGR->HasSystem<DummyComponent>())
		printf("HAS TRANS\n");
	else
		printf("NO TRANS\n");

	if (comp->GetComponent<DYE::Transform>() != nullptr)
		printf("PUS\n");
	
	system("PAUSE");
	return 0;
}
