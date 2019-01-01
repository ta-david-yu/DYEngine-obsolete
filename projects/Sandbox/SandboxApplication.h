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
	IScene* m_pScene00;

	virtual void setupScenes();

	void buildTutScene(IScene* scene);

	void buildTestScene0(IScene* scene);

	void buildTestScene1(IScene* scene);
};

class Scene00 : public IScene
{
	DYE_SCENE_CLASS
	Scene00() : IScene() {}
	virtual void load();
};