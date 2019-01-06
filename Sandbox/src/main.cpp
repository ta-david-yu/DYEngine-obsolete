#include "SandboxApplication.h"

#include <iostream>
#include <cassert>
#include <direct.h>		// _mkdir

using namespace DYE;

int main()
{
	// create log file
	_mkdir("Log");
	FILE* logFile = fopen("Log/log.txt", "w+");
	LOG->SetOutputFile(logFile);

	SandboxApplication* app = new SandboxApplication();
	app->SetWindowName("Sandbox " + TIME->GetDateString());
	app->Run();

	fclose(logFile);

	system("PAUSE");
	return 0;
}
