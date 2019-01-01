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
	assert(RTex->m_TextureType == Texture::TextureType::Texture2D);
	assert(RTex->m_FilteringType == Texture::FilteringType::Linear);
	assert(RTex->m_WrappingType == Texture::WrappingType::ClampToBorder);
	assert(RTex->m_UseMipMap == true);
	assert(RTex->m_MipMapLevel == 5);


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

	printf("ori: %s\n", right.ToString().c_str());
	printf("rot: %s\n", rotRight.ToString().c_str());
	assert(rotRight == right);

	printf("test passed!\n");
}

void Scene02::load()
{
	Entity* ent00 = this->CreateEntity();
	IComponent* comp00 = ent00->AddComponent<ReusablePool>();
	ReusablePool* pool = dynamic_cast<ReusablePool*>(comp00);
	pool->Init();

	ent00->AddComponent<Transform>();

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