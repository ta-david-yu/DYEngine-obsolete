#include <DYEngine\Resource.h>

#include <cassert>
#include <string>
#include <fstream>
#include <streambuf>

namespace DYE
{

	//====================================================================================
	//	IResourceValue
	//====================================================================================
	bool IResourceValue::IsLoaded() const
	{
		return m_pResourceBase->IsProperlyLoaded();
	}

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
	void ResourceBase::AttachResourceValue(IResourceValue* value)
	{
		value->m_pResourceBase = this;
	}

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
		// TO DO:
	}

	bool ResourceManager::Unload(IResourceValue* resrcValue)
	{
		return Unload(resrcValue->GetResourceFileName());
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

	//====================================================================================
	//	Text: text file, stored as string
	//====================================================================================
	bool Text::loadFromFile(const std::string& filename, int argc, void *args)
	{
		const char* filename_c = filename.c_str();

		std::ifstream fileStream(filename_c);

		if ( !fileStream )
		{
			LogError("Error while loading text file \"%-15s\" : Failed to load file.", filename_c);
			return false;
		}

		m_Data = std::string((std::istreambuf_iterator<char>(fileStream)),
							  std::istreambuf_iterator<char>());
	}

	std::string& Text::GetText()
	{
		return m_Data;
	}

}