#pragma once

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <cassert>

#define RESOURCE_MGR ResourceManager::GetInstance()

namespace DYE
{
	class IResourceValue;
	class ResourceManager;

	enum ResourceType
	{
		BASE,
		TEXT,
		SHADER,
		MATERIAL,
		TEXTURE,
		MESH,
	};


	//====================================================================================
	//	ResourceValue: representing a resource that can be loaded from the hardware
	//====================================================================================
	class IResourceValue
	{
		friend class ResourceBase;
	protected:
		std::string m_ResourceFileName;
		// TO DO: check if file exists
		virtual bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) = 0;
	public:
		void SetResourceFileName(const std::string& name);
		std::string GetResourceFileName() const;
	};

	//====================================================================================
	//	ResourceBase: base class for manager to maintain
	//====================================================================================
	class ResourceBase
	{
		friend class ResourceManager;
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		int m_ReferenceCount;
	protected:
		std::string m_ResourceFileName;

		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	method
		//==========================================
	private:
		void incRef() { m_ReferenceCount++; }
		void decRef() { m_ReferenceCount--; }

		// static ResourceBase* CreateResource(ResourceType type, );
	protected:

		//==========================================
		//	getter
		//==========================================
	public:
		std::string GetResourceFileName() const;
		int GetReferenceCount() const;
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	protected:
		ResourceBase(const std::string& filename, int argc = 0, void *args = nullptr);
		~ResourceBase();
	};

	//====================================================================================
	//	Resource: resource are objects that could be reused in many places
	//====================================================================================
	template <class RType>
	class Resource : public ResourceBase
	{
		friend class ResourceManager;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		RType* m_pResourceObject;
		//==========================================
		//	getter
		//==========================================
	public:
		RType* GetValue() const { return m_pResourceObject; }
	
	protected:
		Resource(const std::string& filename, int argc = 0, void *args = nullptr) : ResourceBase(filename, argc, args)
		{
			// TO DO: new RType, 
			// bool isTypeValue = std::is_base_of<IResourceValue, RType>::value;
			// assert(isTypeValue);
			m_pResourceObject = new RType();
			bool isLoaded = m_pResourceObject->loadFromFile(filename, argc, args);

			m_pResourceObject->SetResourceFileName(filename);

			if (!isLoaded)
				LogError("Error while loading resource file : %10s", filename);
		}
	};

	//====================================================================================
	//	ResourceManager: managing resources loaded from the hardware
	//====================================================================================
	class ResourceManager
	{
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		typedef std::pair<std::string, ResourceBase*> ResourcePair;
		typedef std::unordered_map<std::string, ResourceBase*> ResourceMap;
		typedef ResourceMap::iterator ResourceMapItr;
		typedef ResourceMap::const_iterator ResourceMapConstItr;

		static ResourceManager* s_pInstance;
		ResourceMap m_ResourceMap;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	method
		//==========================================
	public:
		std::size_t ResourceCount() const;
	public:
		void ReleaseAll();
		template <class T>
		T* Load(const std::string& filename, int argc = 0, void *args = nullptr);
		bool Unload(const std::string& filename);
		//==========================================
		//	getter
		//==========================================
		static ResourceManager* GetInstance();
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	};

	//====================================================================================
	//	Text: text file
	//====================================================================================
	class Text : public IResourceValue
	{
		//==========================================
		//	memeber/variable
		//==========================================
		friend class Resource<Text>;
	protected:
		bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) override {} // TO DO:
	private:

		//==========================================
		//	method
		//==========================================

		//==========================================
		//	getter
		//==========================================

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	};

	// TO DO: Resource specialization (Text, Material, Mesh, Shader, Texture)
	// Manager keeps seperate list
	template <class T>
	T* ResourceManager::Load(const std::string& filename, int argc, void *args)
	{
		// TO DO: do error handling
		ResourceMapItr itr = m_ResourceMap.find(filename);
		if (itr != m_ResourceMap.end())
		{
			itr->second->incRef();
			return static_cast<Resource<T>*>(itr->second)->GetValue();
		}

		// not yet loaded
		Resource<T>* resrc = new Resource<T>(filename, argc, args);
		resrc->incRef();
		m_ResourceMap.insert(ResourcePair(filename, resrc));
		return resrc->GetValue();
	}
}