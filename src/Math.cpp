#include <DYEngine\utilities\Math.h>

namespace DYE
{
	//====================================================================================
	//	Math: provide with some basic math functions
	//====================================================================================
	const float Math::Rad2Degf = 57.295779513082320876798154814105f; //360.0f / (glm::pi<float>() * 2);
	const float Math::Deg2Radf = 0.01745329251994329576923690768489f; //(glm::pi<float>() * 2) / 360.0f;
	const float Math::PIf = glm::pi<float>();
	const float Math::Elipsonf = glm::epsilon<float>();

	float Math::Abs(const float value)
	{
		return glm::abs(value);
	}

	bool Math::IsEqual(const float lhs, const float rhs)
	{
		return (Abs(lhs - rhs) <= Elipsonf);
	}

	float Math::Cosf(const float _radian)
	{
		return glm::cos(_radian);
	}

	float Math::Sinf(const float _radian)
	{
		return glm::sin(_radian);
	}

	float Math::Tanf(const float _radian)
	{
		return glm::tan(_radian);
	}

	float Math::ACosf(const float _value)
	{
		return glm::acos(_value);
	}

	float Math::ASinf(const float _value)
	{
		return glm::asin(_value);
	}

	float Math::ATanf(const float _value)
	{
		return glm::atan(_value);
	}
}