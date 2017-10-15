
#include <DYEngine\Resource.h>

#include <cassert>

namespace DYE
{

	//====================================================================================
	//	IResourceValue
	//====================================================================================
	void IResourceValue::SetResourceFileName(const std::string& name)
	{
		m_ResourceFileName = name;
	}

	std::string IResourceValue::GetResourceFileName() const
	{
		return m_ResourceFileName;
	}

	//====================================================================================
	//	ResourceBase: base class for manager to maintain
	//====================================================================================
	std::string ResourceBase::GetResourceFileName() const
	{
		return m_ResourceFileName;
	}

	int ResourceBase::GetReferenceCount() const
	{
		return m_ReferenceCount;
	}

	ResourceBase::ResourceBase(const std::string& filename, int argc, void *args) : m_ResourceFileName(filename), m_ReferenceCount(0)
	{

	}

	ResourceBase::~ResourceBase()
	{

	}

	//====================================================================================
	//	Resource: managing resources loaded from the hardware
	//====================================================================================

	//====================================================================================
	//	ResourceManager: managing resources loaded from the hardware
	//====================================================================================
	ResourceManager* ResourceManager::s_pInstance = nullptr;

	ResourceManager* ResourceManager::GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new ResourceManager();
		}
		assert(s_pInstance != nullptr);
		return s_pInstance;
	}

	void ResourceManager::ReleaseAll()
	{

	}

	bool ResourceManager::Unload(const std::string& filename)
	{
		ResourceMapItr itr = m_ResourceMap.find(filename);
		if (itr != m_ResourceMap.end())
		{
			itr->second->decRef();

			if (itr->second->GetReferenceCount() <= 0)
			{
				delete itr->second;
				m_ResourceMap.erase(itr);
			}
			return true;
		}
		return false;
	}

	std::size_t ResourceManager::ResourceCount() const
	{
		return m_ResourceMap.size();
	}
}