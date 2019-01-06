#pragma once

#include "DYEngine/Core.h"

namespace DYE
{
	//====================================================================================
	//	ICallback: Base callback
	//====================================================================================
	template <typename Ret, typename Param0>
	class DYE_API ICallback
	{
	public:
		virtual Ret Invoke(Param0 param0) = 0;
	};

	//====================================================================================
	//	StaticFunctionCallback: static function pointer
	//====================================================================================
	template <typename Ret, typename Param0>
	class DYE_API StaticFunctionCallback : public ICallback<Ret, Param0>
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		Ret (*m_Func)(Param0);
	public:
		//==========================================
		//	method
		//==========================================
		virtual Ret Invoke(Param0 param0)
		{
			return (m_Func)(param0);
		}

		//==========================================
		//	constructor/destructor
		//==========================================
		StaticFunctionCallback(Ret (*func)(Param0)) :
			m_Func(func)
		{

		}
	};

	//====================================================================================
	//	MethodCallback : member function pointer
	//====================================================================================
	template <typename Ret, typename Param0, typename T, typename Method>
	class DYE_API MethodCallback : public ICallback<Ret, Param0>
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		T* m_Object;
		Method m_Method;

	public:
		//==========================================
		//	method
		//==========================================
		virtual Ret Invoke(Param0 param0)
		{
			return (m_Object->*m_Method)(param0);
		}

		//==========================================
		//	constructor/destructor
		//==========================================
		MethodCallback(T* object, Method method) :
			m_Object(object),
			m_Method(method)
		{

		}
	};

	//====================================================================================
	//	Delegate : function delegate
	//====================================================================================
	template <typename Ret, typename Param0>
	class DYE_API Delegate
	{
	private:
		ICallback<Ret, Param0>* m_Callback;

	public:
		//==========================================
		//	method
		//==========================================
		Ret operator()(Param0 param0)
		{
			return m_Callback->Invoke(param0);
		}

		//==========================================
		//	constructor/destructor
		//==========================================
		Delegate(Ret(*func)(Param0)) : 
			m_Callback(new StaticFunctionCallback<Ret, Param0>(func)) { }

		template <typename T, typename Method>
		Delegate(T* object, Method method) : 
			m_Callback(new MethodCallback<Ret, Param0, T, Method>(object, method)) { }

		
		~Delegate() { delete m_Callback; }
	};
}