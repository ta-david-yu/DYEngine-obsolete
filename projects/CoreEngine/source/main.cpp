#include <DYEngine\Main.h>

#include <iostream>
#include <cassert>

using namespace DYE;

void testResource()
{
	Mesh* RMesh = RESOURCE_MGR->Load<Mesh>("", 0, nullptr);
	Mesh* mesh = RMesh;

	printf("test passed!\n");
}

int main()
{
	// create log file
	FILE* logFile = fopen("log.txt", "w+");
	LOG->SetOutputFile(logFile);

	BaseApplication* app = new BaseApplication();
	app->SetWindowName("Demo Game");
	app->Run();

	fclose(logFile);

	system("PAUSE");
	return 0;
}
