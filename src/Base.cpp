#include <DYEngine\Base.h>
#include <DYEngine\Main.h>

#include <typeinfo>
#include <typeindex>

namespace DYE
{
	int Base::s_nextInstantiateID = 0;
	std::set<Base*> Base::s_instancesSet;

	Base::Base()
	{
		m_InstanceID = s_nextInstantiateID++;
		s_instancesSet.insert(this);
	}

	Base::~Base()
	{
		s_instancesSet.erase(this);
	}

	// TO DO:
	void Base::Destroy(Base* _pBase)
	{
		printf("TO BE IMPLEMENTED.");
		_pBase->m_IsToBeDestroyed = true;
	}

	// TO DO:
	Base* Base::Instantiate(const Base* _pOriginal)
	{
		printf("TO BE IMPLEMENTED.");
		return nullptr;
	}

}