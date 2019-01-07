#include "SandboxApplication.h"

#include <iostream>
#include <cassert>

using namespace DYE;

int main()
{
	// create log file
	LOG->SetOutputFile("log.txt");

	SandboxApplication* app = new SandboxApplication();
	app->SetWindowName("Sandbox " + TIME->GetDateString());
	app->Run();

	system("PAUSE");
	return 0;
}
