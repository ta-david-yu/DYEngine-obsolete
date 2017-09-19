#pragma once

#include <string>
#include <set>
#include <vector>
#include <list>

namespace DYE
{
	class Base;

	//====================================================================================
	//	NonCopyable: Restrict copy constructor and assign operator
	//====================================================================================
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	//====================================================================================
	//	Base: Base class that component and entity are derived from
	//====================================================================================
	class Base : public NonCopyable
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static int s_nextInstantiateID;
		static std::set<Base*> s_instancesSet;
		static std::list<Base*> s_toBeDestryoedList;

		int m_InstanceID;
		std::string m_Name;
		bool m_IsToBeDestroyed = false;
	public:
		//==========================================
		//	procedure
		//==========================================
		static void DestructionUpdate();					// Called at the end of the frame to destroy labelled base object in the destroyed set

		//==========================================
		//	method
		//==========================================
		static void Destroy(Base* _pBase);					// Mark this and its component to be destroyed at the end of the frame (delayed destruction)
		static Base* Instantiate(const Base* _pOriginal);	// 
		template <class Type>
		static Base* FindObjectOfType()						// Return a Base object of type Type
		{

		}
		template <class Type>
		static std::vector<Base*> FindObjectsOfType()		// Return all Base objects of type Type TO DO
		{

		}
	protected:
		virtual void release() = 0;							// Need to be implemented for derived class, called on destruction loop
	public:
		//==========================================
		//	getter
		//==========================================
		int GetInstanceID() const { return m_InstanceID; }
		std::string GetName() const { return m_Name; }

		//==========================================
		//	setter
		//==========================================
		void SetName(const std::string& _name) { m_Name = _name; }
		//==========================================
		//	opeartor
		//==========================================
		inline bool operator==(const Base& other) const
		{
			return (other.m_InstanceID == this->m_InstanceID);
		}

		inline bool operator!=(const Base& other) const
		{
			return !operator==(other);
		}
		//==========================================
		//	constructor/destructor
		//==========================================
		Base();
		~Base();
	};
}