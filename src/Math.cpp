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

	//====================================================================================
	//	Vector2f: 2 components float
	//====================================================================================
	Vector2f Vector2f::UnitX()
	{
		return Vector2f(1, 0);
	}

	Vector2f Vector2f::UnitY()
	{
		return Vector2f(0, 1);
	}

	Vector2f Vector2f::Zero()
	{
		return Vector2f(0, 0);
	}

	Vector2f Vector2f::Lerp(const Vector2f& a, const Vector2f& b, const float t)
	{
		return glm::mix(a.main, b.main, t);
	}

	Vector2f Vector2f::Scale(Vector2f& lhs, Vector2f& rhs)
	{
		return Vector2f(lhs.x() * rhs.x(), lhs.y() * rhs.y());
	}

	float Vector2f::Dot(const Vector2f& lhs, const Vector2f& rhs)
	{
		return glm::dot(lhs.main, rhs.main);
	}

	Vector2f::Vector2f() : main(0, 0) {}
	Vector2f::Vector2f(float x, float y) : main(x, y) {}
	Vector2f::Vector2f(const Vector2f& vec) : main(vec.main) {}
	Vector2f::Vector2f(const glm::vec2& vec) : main(vec) {}

	float& Vector2f::x() { return main.x; }
	float& Vector2f::y() { return main.y; }

	float& Vector2f::r() { return main.x; }
	float& Vector2f::g() { return main.y; }

	float Vector2f::Magnitude() const
	{
		return glm::length(main);
	}

	float Vector2f::SqrMagnitude() const
	{
		return main.x * main.x + main.y * main.y;
	}

	Vector2f Vector2f::Normalized() const
	{
		return glm::normalize(main);
	}

	float& Vector2f::operator[](std::size_t i)
	{
		return main.operator[](i);
	}

	Vector2f& Vector2f::operator=(const Vector2f& other)
	{
		this->main = other.main;
		return *this;
	}

	Vector2f Vector2f::operator*(const float& scalar) const
	{
		return main * scalar;
	}

	bool Vector2f::operator==(const Vector2f& other) const
	{
		auto vec2bool = glm::equal(this->main, other.main);
		return vec2bool.x & vec2bool.y;
	}

	bool Vector2f::operator!=(const Vector2f& other) const
	{
		return !operator==(other);
	}

	Vector2f Vector2f::operator+(const Vector2f& other) const
	{
		return main + other.main;
	}

	Vector2f Vector2f::operator-(const Vector2f& other) const
	{
		return main - other.main;
	}

	Vector2f::operator glm::vec2() const
	{
		return main;
	}

	Vector2f::operator glm::vec2()
	{
		return main;
	}

	//====================================================================================
	//	Vector3f: 3 components float
	//====================================================================================
	Vector3f Vector3f::UnitX()
	{
		return Vector3f(1, 0, 0);
	}

	Vector3f Vector3f::UnitY()
	{
		return Vector3f(0, 1, 0);
	}

	Vector3f Vector3f::UnitZ()
	{
		return Vector3f(0, 0, 1);
	}

	Vector3f Vector3f::Lerp(const Vector3f& a, const Vector3f& b, const float t)
	{
		return glm::mix(a.main, b.main, t);
	}

	Vector3f Vector3f::Scale(Vector3f& lhs, Vector3f& rhs)
	{
		return Vector3f(lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z());
	}

	float Vector3f::Dot(const Vector3f& lhs, const Vector3f& rhs)
	{
		return glm::dot(lhs.main, rhs.main);
	}

	Vector3f Vector3f::Cross(const Vector3f& lhs, const Vector3f& rhs)
	{
		return glm::cross(lhs.main, rhs.main);
	}

	Vector3f::Vector3f() : main(0, 0, 0) {}
	Vector3f::Vector3f(float x, float y, float z) : main(x, y, z) {}
	Vector3f::Vector3f(const Vector3f& vec) : main(vec.main) {}
	Vector3f::Vector3f(const Vector2f& vec) : main(vec.main.x, vec.main.y, 0) {}
	Vector3f::Vector3f(const glm::vec3& vec) : main(vec) {}

	float& Vector3f::x() { return main.x; }
	float& Vector3f::y() { return main.y; }
	float& Vector3f::z() { return main.z; }

	float& Vector3f::r() { return main.x; }
	float& Vector3f::g() { return main.y; }
	float& Vector3f::b() { return main.z; }

	float Vector3f::Magnitude() const
	{
		return glm::length(main);
	}

	float Vector3f::SqrMagnitude() const
	{
		return main.x * main.x + main.y * main.y + main.z * main.z;
	}

	Vector3f Vector3f::Normalized() const
	{
		return glm::normalize(main);
	}

	float& Vector3f::operator[](std::size_t i)
	{
		return main.operator[](i);
	}

	Vector3f& Vector3f::operator=(const Vector3f& other)
	{
		this->main = other.main;
		return *this;
	}

	Vector3f Vector3f::operator*(const float& scalar) const
	{
		return main * scalar;
	}

	bool Vector3f::operator==(const Vector3f& other) const
	{
		auto vec3bool = glm::equal(this->main, other.main);
		return vec3bool.x & vec3bool.y & vec3bool.z;
	}

	bool Vector3f::operator!=(const Vector3f& other) const
	{
		return !operator==(other);
	}

	Vector3f Vector3f::operator+(const Vector3f& other) const
	{
		return main + other.main;
	}

	Vector3f Vector3f::operator-(const Vector3f& other) const
	{
		return main - other.main;
	}

	Vector3f::operator glm::vec3() const
	{
		return main;
	}

	Vector3f::operator glm::vec3()
	{
		return main;
	}

	//====================================================================================
	//	Vector4f: 4 components float
	//====================================================================================

	Vector4f Vector4f::UnitX()
	{
		return Vector4f(1, 0, 0, 0);
	}

	Vector4f Vector4f::UnitY()
	{
		return Vector4f(0, 1, 0, 0);
	}

	Vector4f Vector4f::UnitZ()
	{
		return Vector4f(0, 0, 1, 0);
	}

	Vector4f Vector4f::UnitW()
	{
		return Vector4f(0, 0, 1, 1);
	}

	Vector4f Vector4f::Lerp(const Vector4f& a, const Vector4f& b, const float t)
	{
		return glm::mix(a.main, b.main, t);
	}

	Vector4f Vector4f::Scale(Vector4f& lhs, Vector4f& rhs)
	{
		return Vector4f(lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z(), lhs.w() * rhs.w());
	}

	float Vector4f::Dot(const Vector4f& lhs, const Vector4f& rhs)
	{
		return glm::dot(lhs.main, rhs.main);
	}

	Vector4f::Vector4f() : main(0, 0, 0, 0) {}
	Vector4f::Vector4f(float x, float y, float z, float w) : main(x, y, z, w) {}
	Vector4f::Vector4f(const Vector4f& vec) : main(vec.main) {}
	Vector4f::Vector4f(const Vector3f& vec) : main(vec.main.x, vec.main.y, vec.main.z, 0) {}
	Vector4f::Vector4f(const Vector2f& vec) : main(vec.main.x, vec.main.y, 0, 0) {}
	Vector4f::Vector4f(const glm::vec4& vec) : main(vec) {}

	float& Vector4f::x() { return main.x; }
	float& Vector4f::y() { return main.y; }
	float& Vector4f::z() { return main.z; }
	float& Vector4f::w() { return main.w; }

	float& Vector4f::r() { return main.x; }
	float& Vector4f::g() { return main.y; }
	float& Vector4f::b() { return main.z; }
	float& Vector4f::a() { return main.w; }

	float Vector4f::Magnitude() const
	{
		return glm::length(main);
	}

	float Vector4f::SqrMagnitude() const
	{
		return main.x * main.x + main.y * main.y + main.z * main.z + main.w * main.w;
	}

	Vector4f Vector4f::Normalized() const
	{
		return glm::normalize(main);
	}

	float& Vector4f::operator[](std::size_t i)
	{
		return main.operator[](i);
	}

	Vector4f& Vector4f::operator=(const Vector4f& other)
	{
		this->main = other.main;
		return *this;
	}

	Vector4f Vector4f::operator*(const float& scalar) const
	{
		return main * scalar;
	}

	bool Vector4f::operator==(const Vector4f& other) const
	{
		auto vec4bool = glm::equal(this->main, other.main);
		return vec4bool.x & vec4bool.y & vec4bool.z & vec4bool.w;
	}

	bool Vector4f::operator!=(const Vector4f& other) const
	{
		return !operator==(other);
	}

	Vector4f Vector4f::operator+(const Vector4f& other) const
	{
		return main + other.main;
	}

	Vector4f Vector4f::operator-(const Vector4f& other) const
	{
		return main - other.main;
	}

	Vector4f::operator glm::vec4() const
	{
		return main;
	}

	Vector4f::operator glm::vec4()
	{
		return main;
	}
}