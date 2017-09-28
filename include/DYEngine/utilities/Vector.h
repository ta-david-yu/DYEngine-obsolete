#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

namespace DYE
{

	struct Vector2f
	{
		glm::vec2 main;

		float& x() { return main.x; }
		float& y() { return main.y; }

		float& r() { return main.x; }
		float& g() { return main.y; }

		float& operator[](std::size_t i)
		{
			main.operator[](i);
		}

		Vector2f() : main(0, 0) {}
		Vector2f(float x, float y) : main(x, y) {}
		Vector2f(const Vector2f& vec) : main(vec.main) {}
		Vector2f(const glm::vec2& vec) : main(vec) {}

		Vector2f& operator=(const Vector2f& other)
		{
			this->main = other.main;
			return *this;
		}

		operator glm::vec2() const { return main; }

		static Vector2f UnitX()
		{
			return Vector2f(1, 0);
		}

		static Vector2f UnitY()
		{
			return Vector2f(0, 1);
		}

		static Vector2f Zero()
		{
			return Vector2f(0, 0);
		}
	};

	struct Vector3f
	{
		glm::vec3 main;

		float& x() { return main.x; }
		float& y() { return main.y; }
		float& z() { return main.z; }

		float& r() { return main.x; }
		float& g() { return main.y; }
		float& b() { return main.z; }

		float& operator[](std::size_t i)
		{
			main.operator[](i);
		}

		Vector3f() : main(0, 0, 0) {}
		Vector3f(float x, float y, float z) : main(x, y, z) {}
		Vector3f(const Vector3f& vec) : main(vec.main) {}
		Vector3f(const Vector2f& vec) : main(vec.main.x, vec.main.y, 0) {}
		Vector3f(const glm::vec3& vec) : main(vec) {}

		Vector3f& operator=(const Vector3f& other)
		{
			this->main = other.main;
			return *this;
		}

		operator glm::vec3() const { return main; }

		static Vector3f UnitX()
		{
			return Vector3f(1, 0, 0);
		}

		static Vector3f UnitY()
		{
			return Vector3f(0, 1, 0);
		}

		static Vector3f UnitZ()
		{
			return Vector3f(0, 0, 1);
		}
	};

	struct Vector4f
	{
		glm::vec4 main;

		float& x() { return main.x; }
		float& y() { return main.y; }
		float& z() { return main.z; }
		float& w() { return main.w; }

		float& r() { return main.x; }
		float& g() { return main.y; }
		float& b() { return main.z; }
		float& a() { return main.w; }

		float& operator[](std::size_t i)
		{
			main.operator[](i);
		}

		Vector4f() : main(0, 0, 0, 0) {}
		Vector4f(float x, float y, float z, float w) : main(x, y, z, w) {}
		Vector4f(const Vector4f& vec) : main(vec.main) {}
		Vector4f(const Vector3f& vec) : main(vec.main.x, vec.main.y, vec.main.z, 0) {}
		Vector4f(const Vector2f& vec) : main(vec.main.x, vec.main.y, 0, 0) {}
		Vector4f(const glm::vec4& vec) : main(vec) {}

		Vector4f& operator=(const Vector4f& other)
		{
			this->main = other.main;
			return *this;
		}

		operator glm::vec4() const { return main; }

		static Vector4f UnitX()
		{
			return Vector4f(1, 0, 0, 0);
		}

		static Vector4f UnitY()
		{
			return Vector4f(0, 1, 0, 0);
		}

		static Vector4f UnitZ()
		{
			return Vector4f(0, 0, 1, 0);
		}

		static Vector4f UnitW()
		{
			return Vector4f(0, 0, 1, 1);
		}
	};

	struct Quaternion
	{
		glm::quat main;

		Vector3f GetEulerAngles() const
		{
			return glm::degrees(glm::eulerAngles(main));
		}

		void SetEulerAngles(const Vector3f& _euler)
		{
			main = glm::quat(_euler);
		}

		Quaternion() : main(glm::vec3(0, 0, 0)) {}
		Quaternion(const Quaternion& quat) : main(quat.main) {}
		Quaternion(Vector3f& euler) 
		{
			glm::vec3 rad(glm::radians(euler.x()), glm::radians(euler.y()), glm::radians(euler.z()));
			main = glm::quat(rad);
		}

		Quaternion& operator=(const Quaternion& other)
		{
			this->main = other.main;
			return *this;
		}
		
		Vector3f operator*(const Vector3f& vec) const
		{
			// TO DO: calculate rotation vector
			return Vector3f();
		}

		static Quaternion Identity()
		{
			return Quaternion();
		}
	};
}