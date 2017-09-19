#include <DYEngine\Base.h>
#include <DYEngine\Main.h>

#include <typeinfo>
#include <typeindex>

namespace DYE
{
	int Base::s_nextInstantiateID = 0;
	std::set<Base*> Base::s_instancesSet;
	std::list<Base*> Base::s_toBeDestryoedList;

	Base::Base()
	{
		m_InstanceID = s_nextInstantiateID++;
		s_instancesSet.insert(this);
	}

	Base::~Base()
	{
		s_instancesSet.erase(this);
	}

	void Base::DestructionUpdate()
	{
		for (auto const &base : s_toBeDestryoedList)
		{
			base->release();
		}
		s_toBeDestryoedList.clear();
	}

	void Base::Destroy(Base* _pBase)
	{
		_pBase->m_IsToBeDestroyed = true;
		s_toBeDestryoedList.push_back(_pBase);
	}

	Base* Base::Instantiate(const Base* _pOriginal)
	{
		printf("TO BE IMPLEMENTED.");
		return nullptr;
	}

}