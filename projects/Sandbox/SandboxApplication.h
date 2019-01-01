#pragma once

#include <DYEngine/Main.h>

using namespace DYE;

//====================================================================================
//	BaseApp: example application
//====================================================================================
class SandboxApplication : public IApplication
{
public:
	SandboxApplication() {}
	~SandboxApplication() {}

private:
	// user define function
	IScene* m_pTutScene;
	IScene* m_pTestScene0;
	IScene* m_pTestScene1;

	virtual void setupScenes();

	void buildTutScene(IScene* scene);

	void buildTestScene0(IScene* scene);

	void buildTestScene1(IScene* scene);
};