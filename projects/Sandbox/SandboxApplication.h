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
	IScene* m_pScene01;
	IScene* m_pScene02;

	virtual void setupScenes();
};

class Scene00 : public IScene
{
	DYE_SCENE_CLASS
	Scene00() : IScene() {}
	virtual void load();
};

class Scene01 : public IScene
{
	DYE_SCENE_CLASS
	Scene01() : IScene() {}
	virtual void load();
};

class Scene02 : public IScene
{
	DYE_SCENE_CLASS
	Scene02() : IScene() {}
	virtual void load();
};