#pragma once

#include <DYEngine/utilities/Logger.h>

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <cassert>

#define RESOURCE_MGR ResourceManager::GetInstance()

// every resource value should have this macro declared
// note that u can specified certain kind of resource to be only put under a certain path
#define DYE_RESOURCE_PATH(X) static std::string SpecificFilePath()						\
		{																				\
			std::string str = X;														\
			return str;																	\
		}

#ifndef RESOURCE_PATH
	#define RESOURCE_PATH "resources/"
#endif // !RESOURCE_PATH

#ifndef MATERIAL_PATH
	#define MATERIAL_PATH "material/"
#endif // !MATERIAL_PATH

#ifndef TEXTURE_PATH
	#define TEXTURE_PATH "texture/"
#endif // !TEXTURE_PATH

#ifndef IMAGE_PATH
	#define IMAGE_PATH "image/"
#endif // !IMAGE_PATH

#ifndef SHADER_PATH
	#define SHADER_PATH "shader/"
#endif // !SHADER_PATH

#ifndef MESH_PATH
	#define MESH_PATH "mesh/"
#endif // !MESH_PATH

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
		IMAGE,
		MESH,
	};


	//====================================================================================
	//	ResourceValue: representing a resource that can be loaded from the hardware
	//====================================================================================
	class IResourceValue
	{
		friend class ResourceBase;
	public:
		DYE_RESOURCE_PATH("")

	protected:
		ResourceBase* m_pResourceBase;

		std::string m_ResourceFileName;
		// TO DO: check if file exists
		virtual bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) = 0;
	public:
		bool IsLoaded() const;
		void SetResourceFileName(const std::string& name);
		std::string GetResourceFileName() const;

		virtual ~IResourceValue() { }
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
		bool m_IsProperlyLoaded = false;
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

		// static ResourceBase* CreateResource(ResourceType type, );	 TO DO
	protected:
		void AttachResourceValue(IResourceValue* value);
		//==========================================
		//	getter
		//==========================================
	public:
		bool IsProperlyLoaded() const { return m_IsProperlyLoaded; }
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
		virtual ~ResourceBase();
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
		RType* m_pResourceValue;
		//==========================================
		//	getter
		//==========================================
	public:
		RType* GetValue() const { return m_pResourceValue; }
	
	protected:
		Resource(const std::string& filename, int argc = 0, void *args = nullptr) : ResourceBase(filename, argc, args)
		{
			// create value
			m_pResourceValue = new RType();
			m_IsProperlyLoaded = m_pResourceValue->loadFromFile(filename, argc, args);

			// attach value
			AttachResourceValue(m_pResourceValue);
			m_pResourceValue->SetResourceFileName(filename);

			if (!m_IsProperlyLoaded)
				LogError("Error loading resource file : %-10s", filename.c_str());
			else
				LogInfo("Load resource file: %-10s", filename.c_str());
		}

		virtual ~Resource() { delete m_pResourceValue; }
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
		using ResourcePair = std::pair<std::string, ResourceBase*>;
		using ResourceMap = std::unordered_map<std::string, ResourceBase*>;
		using ResourceMapItr = ResourceMap::iterator;
		using ResourceMapConstItr = ResourceMap::const_iterator;

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
		bool Unload(IResourceValue* resrcValue);
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
	//	ScopeBasedResourceHandler: Unload resource pointer when Handler is destroyed
	//====================================================================================
	template<class Resrc>
	class ScopeBasedResourceHandler
	{
		//==========================================
		//	memeber/variable
		//==========================================
		Resrc* m_pResource = nullptr;

		//==========================================
		//	getter/setter
		//==========================================
	public:
		inline Resrc* GetResourcePtr() { return m_pResource; }
		inline void SetResourcePtr(Resrc* _resrc) { m_pResource = _resrc; }
		inline void SetResourcePtr(const Resrc* _resrc) { m_pResource = _resrc; }

		inline Resrc& operator*() { return *m_pResource; }
		inline Resrc& operator*() const { return *m_pResource; }

		inline Resrc* operator->() { return m_pResource; }
		inline Resrc* operator->() const { return m_pResource; }

		//==========================================
		//	constructor/destructor
		//==========================================
		ScopeBasedResourceHandler()
		{

		}

		ScopeBasedResourceHandler(Resrc* resrc) : m_pResource(resrc)
		{
			static_assert(std::is_base_of<IResourceValue, Resrc>::value, "Invalid resource type for ResourceHandler.");
		}

		~ScopeBasedResourceHandler()
		{
			if (m_pResource != nullptr)
				RESOURCE_MGR->Unload(m_pResource);
		}
	};

	//====================================================================================
	//	Text: text file
	//====================================================================================
	class Text : public IResourceValue
	{
		friend class Resource<Text>;
	public:
		DYE_RESOURCE_PATH("")

		//==========================================
		//	memeber/variable
		//==========================================
	private:
		std::string m_Data;

		//==========================================
		//	method
		//==========================================
	protected:
		bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) override;

		//==========================================
		//	getter
		//==========================================
	public:
		std::string& GetText();

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	};

	// Manager keeps seperate list TO DO: maybe
	template <class T>
	T* ResourceManager::Load(const std::string& filename, int argc, void *args)
	{
		static_assert(std::is_base_of<IResourceValue, T>::value, "Invalid resource type for ResourceManager::Load.");

		// get full file path
		std::string fullPathFileName = RESOURCE_PATH;
		fullPathFileName += T::SpecificFilePath() + filename;

		// find if already loaded
		ResourceMapItr itr = m_ResourceMap.find(fullPathFileName);
		if (itr != m_ResourceMap.end())
		{
			itr->second->incRef();
			return static_cast<Resource<T>*>(itr->second)->GetValue();
		}

		// load new resources
		Resource<T>* resrc = new Resource<T>(fullPathFileName, argc, args);

		// return null if is not properly loaded
		if (!resrc->IsProperlyLoaded())
		{
			delete resrc;
			return nullptr;
		}

		resrc->incRef();

		// add to the resource map
		m_ResourceMap.insert(ResourcePair(fullPathFileName, resrc));
		return resrc->GetValue();
	}
}