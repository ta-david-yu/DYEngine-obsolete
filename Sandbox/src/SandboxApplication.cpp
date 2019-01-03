#include "SandboxApplication.h"

void SandboxApplication::setupScenes()
{
	//m_pTutScene = createScene(&BaseApplication::buildTutScene);
	//m_pTestScene0 = createScene(&BaseApplication::buildTestScene0);
	m_pScene00 = SCENE_MGR->CreateScene<Scene00>();
	m_pScene01 = SCENE_MGR->CreateScene<Scene01>();
	m_pScene02 = SCENE_MGR->CreateScene<Scene02>();
}

void Scene00::load()
{
	// prototype
	Entity* root = this->CreateEntity("Root");
	root->AddComponent<DebugCPUComponent>()->Init();
	root->GetTransform()->SetPosition(Vector3f(0, 0, 0));
	root->GetTransform()->SetLocalScale(Vector3f(0, 0, 0));


	Entity* ent0 = this->CreateEntity("Nod0");
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

	// Base::printAllBaseObj();

	//printf("%s\n", root->ToString());

	SYSTEM_MGR->EarlyUpdate();

	Mesh* RMesh = RESOURCE_MGR->Load<Mesh>("123456", 0, nullptr);
	Mesh* mesh = RMesh;


	Texture* RTex = RESOURCE_MGR->Load<Texture>("test_texture.texture", 0, nullptr);

	DYE_ASSERT(RTex->m_TextureType == Texture::TextureType::Texture2D, "");
	DYE_ASSERT(RTex->m_FilteringType == Texture::FilteringType::Linear, "");
	DYE_ASSERT(RTex->m_WrappingType == Texture::WrappingType::ClampToBorder, "");
	DYE_ASSERT(RTex->m_UseMipMap == true, "");
	DYE_ASSERT(RTex->m_MipMapLevel == 5, "");


	Text* RText = RESOURCE_MGR->Load<Text>("test.txt");

	Material* RMat = RESOURCE_MGR->Load<Material>("test_material.material", 0, nullptr);

	RESOURCE_MGR->Unload(RMat);
	RESOURCE_MGR->Unload(RTex);
}

void Scene01::load()
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

	DYE_ASSERT(unitX == normX, "");
	DYE_ASSERT(unitY == normY, "");
	DYE_ASSERT(x == normX, "");
	DYE_ASSERT(y == normY, "");
	DYE_ASSERT(unitX != normY, "");
	DYE_ASSERT(unitY != normX, "");
	DYE_ASSERT(x != normY, "");
	DYE_ASSERT(y != normX, "");
	DYE_ASSERT(x == bigX.Normalized(), "");
	DYE_ASSERT(y == bigY.Normalized(), "");

	DYE_ASSERT(Math::IsEqual(bigX.Magnitude(), bigY.Magnitude()), "");
	DYE_ASSERT(bigXY == (bigX + bigY), "");

	Vector2f x2 = Vector2f::UnitX();
	Vector2f x2_0 = Vector2f::UnitX();
	DYE_ASSERT(x2 == x2_0, "");

	Vector3f forward = Vector3f::UnitZ();
	Vector3f right = Vector3f::UnitX();
	Quaternion fToR = Quaternion(Vector3f(0, 90, 0));

	Vector3f rotRight = fToR * forward;

	printf("ori: %s\n", right.ToString().c_str());
	printf("rot: %s\n", rotRight.ToString().c_str());
	DYE_ASSERT(rotRight == right, "");

	printf("test passed!\n");
}

void Scene02::load()
{
	Entity* ent00 = this->CreateEntity();
	IComponent* comp00 = ent00->AddComponent<ReusablePool>();
	ReusablePool* pool = dynamic_cast<ReusablePool*>(comp00);
	pool->Init();

	ent00->AddComponent<Transform>();

	DYE_ASSERT(SYSTEM_MGR->HasSystem<ReusablePool>(), "");

	DYE_ASSERT(SYSTEM_MGR->HasSystem<Transform>(), "");

	DYE_ASSERT(comp00->GetComponent<Transform>() == comp00->GetTransform(), "");

	DYE_ASSERT(!SYSTEM_MGR->HasSystem<DebugCPUComponent>(), "");

	ent00->SetName("Obj00_v1");
	DYE_ASSERT(comp00->GetName() == "Obj00_v1", "");
	DYE_ASSERT(ent00->GetName() == "Obj00_v1", "");

	comp00->SetName("Obj00_v2");
	DYE_ASSERT(comp00->GetName() == "Obj00_v2", "");
	DYE_ASSERT(ent00->GetName() == "Obj00_v2", "");

	ent00->SetName("Obj00_v3");
	DYE_ASSERT(comp00->GetName() == "Obj00_v3", "");
	DYE_ASSERT(ent00->GetName() == "Obj00_v3", "");

	comp00->SetName("Obj00_v4");
	DYE_ASSERT(comp00->GetName() == "Obj00_v4", "");
	DYE_ASSERT(ent00->GetName() == "Obj00_v4", "");

	printf("test passed!\n");
}