#include <DYEngine\interfaces\IApplication.h>

namespace DYE
{
	void IApplication::init()
	{
		m_pCore = new Core(this);
	}

	void IApplication::gameLoop()
	{
		// create scene, load scene function into each scene
		createScene();

		// notice that the scene SceneID == 0 is always the first loaded scene
		CORE->loadScene(CORE->m_CurrScene);

		// TO DO: game loop
	}
}