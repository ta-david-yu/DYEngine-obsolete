#include <DYEngine\Main.h>

#include <iostream>
#include <cassert>

using namespace DYE;

void testResource()
{
	Resource<Mesh>* RMesh = RESOURCE_MGR->Load<Mesh>("", 0, nullptr);
	Mesh* mesh = RMesh->GetValue();

	printf("test passed!\n");
}

int main()
{
	BaseApplication* app = new BaseApplication();
	app->SetWindowName("Demo Game");
	app->Run();

	system("PAUSE");
	return 0;
}
