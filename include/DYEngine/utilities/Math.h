#pragma once

#include <DYEngine\utilities\Rect.h>
#include <DYEngine\utilities\Vector.h>

#define GLM_FORCE_RADIANS

namespace DYE
{
	//====================================================================================
	//	Math: provide with some basic math functions
	//====================================================================================
	struct Math
	{
		static const float Rad2Degf; //360.0f / (glm::pi<float>() * 2);
		static const float Deg2Radf; //(glm::pi<float>() * 2) / 360.0f;
		static const float PIf;
		static const float Elipsonf;
		
		static float Abs(const float value);
		static bool IsEqual(const float lhs, const float rhs);

		static float Cosf(const float _radian);
		static float Sinf(const float _radian);
		static float Tanf(const float _radian);

		static float ACosf(const float _value);
		static float ASinf(const float _value);
		static float ATanf(const float _value);
	};
}