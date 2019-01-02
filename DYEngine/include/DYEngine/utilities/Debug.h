#pragma once

#include <DYEngine/Core.h>

#include <type_traits>

namespace DYE
{
	struct DYE_API Debug
	{
		template <class Type>
		static std::string ClassName()
		{
			return std::string(typeid(Type).name());
		}

		template <class Type>
		static std::string ClassName(Type* ptr)
		{
			return std::string(typeid(Type).name());
		}
	};
}