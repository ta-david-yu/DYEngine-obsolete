#pragma once

#include <string>
#include <set>

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

		int m_InstanceID;
		std::string m_Name;
		bool m_IsToBeDestroyed = false;
	protected:
		//==========================================
		//	setter
		//==========================================
		void SetName(const std::string& _name) { m_Name = _name; }
	public:
		//==========================================
		//	method
		//==========================================
		static void Destroy(Base* _pBase);					// Mark this and its component to be destroyed at the end of the frame
		static Base* Instantiate(const Base* _pOriginal);

		//==========================================
		//	getter
		//==========================================
		int GetInstanceID() const { return m_InstanceID; }
		std::string GetName() const { return m_Name; }
		
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