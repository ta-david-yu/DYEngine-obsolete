#include <DYEngine\Main.h>

#include "SandboxApplication.h"

#include <iostream>
#include <cassert>

using namespace DYE;

int main()
{
	// create log file
	FILE* logFile = fopen("log.txt", "w+");
	LOG->SetOutputFile(logFile);

	SandboxApplication* app = new SandboxApplication();
	app->SetWindowName("Sandbox " + TIME->GetDateString());
	app->Run();

	fclose(logFile);

	system("PAUSE");
	return 0;
}
