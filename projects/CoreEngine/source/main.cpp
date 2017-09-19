#include <DYEngine\Main.h>

#include <iostream>

using namespace DYE;

int main()
{
	Entity ent;
	Entity ent1;
	ent.SetName("Obj8");
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
	
	std::cout << comp->GetTransform()->GetName() << std::endl;

	if (ent.GetTransform() != ent1.GetTransform())
		printf("is not equal\n");

	if (ent1.GetTransform() == comp->GetTransform())
		printf("is equal\n");

	system("PAUSE");
	return 0;
}
