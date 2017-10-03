#pragma once

#include <type_traits>

namespace DYE
{
	struct Debug
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