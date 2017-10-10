#include <DYEngine\Base.h>
#include <DYEngine\Entity.h>
#include <DYEngine\interfaces\IComponent.h>

#include <typeinfo>
#include <typeindex>

namespace DYE
{
	//====================================================================================
	//	Base: Base class that component and entity are derived from
	//====================================================================================

	InstanceID Base::s_nextInstantiateID = 0;
	std::set<Base*> Base::s_instancesSet;
	std::vector<Base*> Base::s_toBeDestryoedList;

	Base::Base() : m_InstanceID(s_nextInstantiateID++)
	{
		printf("ID: %d \n", s_nextInstantiateID - 1);
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
		// assert(false);
		// TO DO: this is evil, still need some tweaking

		Entity* clone = nullptr;
		const Entity* ent = dynamic_cast<const Entity*>(_pOriginal);
		if (ent != nullptr)
		{
			// is entity, copy entity
			IScene* scene = ent->m_pScene;

			clone = scene->CreateEntity(ent->GetName());
			clone->copyFrom(ent);
		}
		else
		{
			const IComponent* comp = dynamic_cast<const IComponent*>(_pOriginal);
			if (comp != nullptr)
			{
				// is component, copy its entity
				ent = comp->GetEntity();
				IScene* scene = ent->m_pScene;

				clone = scene->CreateEntity(ent->GetName());
				clone->copyFrom(ent);
			}
			else
			{
				// TO DO: error log
				printf("ERROR BASE OBJECT CASTING\n");
			}
		}

		return clone;
	}

}