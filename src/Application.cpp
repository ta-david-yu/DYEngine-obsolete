#include <DYEngine\interfaces\IApplication.h>
#include <DYEngine\Time.h>

namespace DYE
{

	void IApplication::Run()
	{
		init();
		gameLoop();
		release();
	}

	void IApplication::init()
	{
		m_pCore = new Core(this);
		m_pCore->init();
	}

	void IApplication::gameLoop()
	{
		// create scene, load scene function into each scene
		setupScenes();

		TIME->tickInit();

		// notice that the scene SceneID == 0 is always the first loaded scene
		SCENE_MGR->loadScene(0);

		// system loop block
		{
			while (true)
			{
				SYSTEM_MGR->Awake();

				SYSTEM_MGR->Start();

				double fixedUpdateLag = 0.0f;

				int framesCounter = 0;
				double timeAccumulator = 0;

				do
				{
					////// FPS //////
					framesCounter++;
					timeAccumulator += TIME->frameDuration();
					if (timeAccumulator > 1.0f)
					{
						double fps = framesCounter / timeAccumulator;
						printf("FPS: %f  %f\n", fps, timeAccumulator);

						timeAccumulator = 0;
						framesCounter = 0;
					}
					////// FPS //////

					SYSTEM_MGR->EarlyUpdate();			// EarlyUpdate

					fixedUpdateLag += TIME->frameDuration();

					while (fixedUpdateLag >= TIME->UnScaled_FixedDeltaTime())
					{
						SYSTEM_MGR->FixedUpdate();		// FixedUpdate
						fixedUpdateLag -= TIME->UnScaled_FixedDeltaTime();
					}

					SYSTEM_MGR->Update();				// Update
						
					SYSTEM_MGR->LateUpdate();			// LateUpdate

					// TO DO: Render Update

					Base::DestructionUpdate();			// Delay Destruction for Base Object (Entity, Component...)

					TIME->tickUpdate();					// Update timer

				} while (!SCENE_MGR->IsLoadingNextScene());

				SCENE_MGR->loadNextScene();
			}
		}
	}

	void IApplication::release()
	{

	}

	IApplication::IApplication()
	{

	}

	IApplication::~IApplication()
	{

	}

	//====================================================================================
	//	BaseApp: example application
	//====================================================================================
	void BaseApplication::setupScenes()
	{
		//m_pTutScene = createScene(&BaseApplication::buildTutScene);
		//m_pTestScene0 = createScene(&BaseApplication::buildTestScene0);
		m_pTestScene1 = createScene(&BaseApplication::buildTestScene1);

	}

	void BaseApplication::buildTutScene(IScene* scene)
	{
		Entity* ent00 = scene->CreateEntity();
		IComponent* comp00 = ent00->AddComponent<ReusablePool>();
		ReusablePool* pool = dynamic_cast<ReusablePool*>(comp00);
		pool->Init();

		assert(SYSTEM_MGR->HasSystem<ReusablePool>());

		assert(SYSTEM_MGR->HasSystem<Transform>());

		assert(comp00->GetComponent<Transform>() == comp00->GetTransform());

		assert(!SYSTEM_MGR->HasSystem<DebugCPUComponent>());

		ent00->SetName("Obj00_v1");
		assert(comp00->GetName() == "Obj00_v1");
		assert(ent00->GetName() == "Obj00_v1");

		comp00->SetName("Obj00_v2");
		assert(comp00->GetName() == "Obj00_v2");
		assert(ent00->GetName() == "Obj00_v2");

		ent00->SetName("Obj00_v3");
		assert(comp00->GetName() == "Obj00_v3");
		assert(ent00->GetName() == "Obj00_v3");

		comp00->SetName("Obj00_v4");
		assert(comp00->GetName() == "Obj00_v4");
		assert(ent00->GetName() == "Obj00_v4");

		printf("test passed!\n");
	}

	void BaseApplication::buildTestScene0(IScene* scene)
	{
		//-------------Test Math Type-------------//
		Vector3f unitX = Vector3f::UnitX();
		Vector3f unitY = Vector3f::UnitY();

		Vector3f normX = unitX.Normalized();
		Vector3f normY = unitY.Normalized();

		Vector3f x(1, 0, 0);
		Vector3f y(0, 1, 0);

		float value = 25;
		Vector3f bigX(value, 0, 0);
		Vector3f bigY(0, value, 0);
		Vector3f bigXY(value, value, 0);

		assert(unitX == normX);
		assert(unitY == normY);
		assert(x == normX);
		assert(y == normY);
		assert(unitX != normY);
		assert(unitY != normX);
		assert(x != normY);
		assert(y != normX);
		assert(x == bigX.Normalized());
		assert(y == bigY.Normalized());

		assert(Math::IsEqual(bigX.Magnitude(), bigY.Magnitude()));
		assert(bigXY == (bigX + bigY));

		Vector2f x2 = Vector2f::UnitX();
		Vector2f x2_0 = Vector2f::UnitX();
		assert(x2 == x2_0);

		Vector3f forward = Vector3f::UnitZ();
		Vector3f right = Vector3f::UnitX();
		Quaternion fToR = Quaternion(Vector3f(0, 90, 0));

		Vector3f rotRight = fToR * forward;

		printf("ori: %s\n", right.ToString());
		printf("rot: %s\n", rotRight.ToString());
		assert(rotRight == right);

		printf("test passed!\n");
	}

	void BaseApplication::buildTestScene1(IScene* scene)
	{
		// prototype
		Entity* root = scene->CreateEntity("Root");
		root->AddComponent<DebugCPUComponent>()->Init();
		root->GetTransform()->SetPosition(Vector3f(0, 0, 0));
		root->GetTransform()->SetLocalScale(Vector3f(0, 0, 0));
		

		Entity* ent0 = scene->CreateEntity("Nod0");
		ent0->GetTransform()->SetParent(root->GetTransform());
		ent0->GetTransform()->SetPosition(Vector3f(1, 1, 1));
		ent0->GetTransform()->SetLocalScale(Vector3f(0, 90, 0));

		ent0->SetActive(false);

		// clone
		Entity* cEnt[4];

		for (int i = 0; i < 4; i++)
		{
			cEnt[i] = dynamic_cast<Entity*>(Base::Instantiate(root));
			cEnt[i]->GetTransform()->SetParent(ent0->GetTransform());
		}

		cEnt[2]->GetTransform()->SetParent(cEnt[3]->GetTransform());

		printf("%s\n", root->ToString());

		SYSTEM_MGR->EarlyUpdate();

		printf("\n%s\n", root->ToString());
	}
}