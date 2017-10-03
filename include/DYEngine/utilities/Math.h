#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\epsilon.hpp>

#define GLM_FORCE_RADIANS

namespace DYE
{
	struct Vector2f;
	struct Vector3f;
	struct Vector4f;
	struct Mat2x2;
	struct Mat3x3;
	struct Mat4x4;
	struct Quaternion;

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
	
	//====================================================================================
	//	Vector2f: 2 components float
	//====================================================================================
	struct Vector2f
	{
		//==========================================
		//	memeber/variable
		//==========================================
		glm::vec2 main;

		//==========================================
		//	static method
		//==========================================
		static Vector2f UnitX();

		static Vector2f UnitY();

		static Vector2f Zero();

		static Vector2f Lerp(const Vector2f& a, const Vector2f& b, const float t);
		static Vector2f Scale(Vector2f& lhs, Vector2f& rhs);
		static float Dot(const Vector2f& lhs, const Vector2f& rhs);

		//==========================================
		//	constructor
		//==========================================
		Vector2f();
		Vector2f(float x, float y);
		Vector2f(const Vector2f& vec);
		Vector2f(const glm::vec2& vec);

		//==========================================
		//	method/operator
		//==========================================
		float& x();
		float& y();

		float& r();
		float& g();

		float Magnitude() const;
		float SqrMagnitude() const;
		Vector2f Normalized() const;

		float& operator[](std::size_t i);
		Vector2f& operator=(const Vector2f& other);
		Vector2f operator*(const float& scalar) const;
		bool operator==(const Vector2f& other) const;
		bool operator!=(const Vector2f& other) const;
		Vector2f operator+(const Vector2f& other) const;
		Vector2f operator-(const Vector2f& other) const;

		operator glm::vec2() const;
		operator glm::vec2();
	};

	//====================================================================================
	//	Vector3f: 3 components float
	//====================================================================================
	struct Vector3f
	{
		//==========================================
		//	memeber/variable
		//==========================================
		glm::vec3 main;

		//==========================================
		//	static method
		//==========================================
		static Vector3f UnitX();

		static Vector3f UnitY();

		static Vector3f UnitZ();

		static Vector3f Lerp(const Vector3f& a, const Vector3f& b, const float t);
		static Vector3f Scale(Vector3f& lhs, Vector3f& rhs);
		static float Dot(const Vector3f& lhs, const Vector3f& rhs);
		static Vector3f Cross(const Vector3f& lhs, const Vector3f& rhs);

		//==========================================
		//	constructor
		//==========================================
		Vector3f();
		Vector3f(float x, float y, float z);
		Vector3f(const Vector3f& vec);
		Vector3f(const Vector2f& vec);
		Vector3f(const glm::vec3& vec);

		//==========================================
		//	method/operator
		//==========================================
		float& x();
		float& y();
		float& z();
				  
		float& r();
		float& g();
		float& b();

		float Magnitude() const;
		float SqrMagnitude() const;
		Vector3f Normalized() const;

		float& operator[](std::size_t i);
		Vector3f& operator=(const Vector3f& other);
		Vector3f operator*(const float& scalar) const;
		bool operator==(const Vector3f& other) const;
		bool operator!=(const Vector3f& other) const;
		Vector3f operator+(const Vector3f& other) const;
		Vector3f operator-(const Vector3f& other) const;

		operator glm::vec3() const;
		operator glm::vec3();
	};

	//====================================================================================
	//	Vector4f: 4 components float
	//====================================================================================
	struct Vector4f
	{
		//==========================================
		//	memeber/variable
		//==========================================
		glm::vec4 main;

		//==========================================
		//	static method
		//==========================================
		static Vector4f UnitX();

		static Vector4f UnitY();

		static Vector4f UnitZ();

		static Vector4f UnitW();

		static Vector4f Lerp(const Vector4f& a, const Vector4f& b, const float t);
		static Vector4f Scale(Vector4f& lhs, Vector4f& rhs);
		static float Dot(const Vector4f& lhs, const Vector4f& rhs);

		//==========================================
		//	constructor
		//==========================================
		Vector4f();
		Vector4f(float x, float y, float z, float w);
		Vector4f(const Vector4f& vec);
		Vector4f(const Vector3f& vec);
		Vector4f(const Vector2f& vec);
		Vector4f(const glm::vec4& vec);

		//==========================================
		//	method/operator
		//==========================================
		float& x();
		float& y();
		float& z();
		float& w();
				  
		float& r();
		float& g();
		float& b();
		float& a();

		float Magnitude() const;
		float SqrMagnitude() const;
		Vector4f Normalized() const;

		float& operator[](std::size_t i);
		Vector4f& operator=(const Vector4f& other);
		Vector4f operator*(const float& scalar) const;
		bool operator==(const Vector4f& other) const;
		bool operator!=(const Vector4f& other) const;
		Vector4f operator+(const Vector4f& other) const;
		Vector4f operator-(const Vector4f& other) const;

		operator glm::vec4() const;

		operator glm::vec4();
	};

	//====================================================================================
	//	Mat2x2: Matric of float with 2 rows and 2 cols
	//====================================================================================
	struct Mat2x2
	{
		//==========================================
		//	memeber/variable
		//==========================================
		glm::mat2 main;

		//==========================================
		//	static method
		//==========================================
		static Mat2x2 Inverse(const Mat2x2& mat)
		{
			return mat.Inverse();
		}

		static float Determinant(const Mat2x2& mat)
		{
			return mat.Determinant();
		}
		//==========================================
		//	constructor
		//==========================================
		Mat2x2() : main() {}
		Mat2x2(const Mat2x2& other) : main(other.main) {}
		Mat2x2(const glm::mat2& other) : main(other) {}
		Mat2x2(const float& scalar) : main(scalar) {}
		Mat2x2(const float& a1, const float& a2,
			const float& a3, const float& a4) : main(a1, a2, a3, a4) {}
		Mat2x2(const float ary[4]) : main(ary[0], ary[1], ary[2], ary[3]) {}
		//==========================================
		//	method/operator
		//==========================================
		Mat2x2 Inverse() const
		{
			return glm::inverse(main);
		}

		float Determinant() const
		{
			return glm::determinant(main);
		}

		Mat2x2& operator=(const Mat2x2& other)
		{
			this->main = other.main;
			return *this;
		}

		operator glm::mat2() const
		{
			return main;
		}

		operator glm::mat2()
		{
			return main;
		}
	};

	//====================================================================================
	//	Mat3x3: Matric of float with 3 rows and 3 cols
	//====================================================================================
	struct Mat3x3
	{
		//==========================================
		//	memeber/variable
		//==========================================
		glm::mat3 main;
		//==========================================
		//	static method
		//==========================================
		static Mat3x3 Inverse(const Mat3x3& mat)
		{
			return mat.Inverse();
		}

		static float Determinant(const Mat3x3& mat)
		{
			return mat.Determinant();
		}

		//==========================================
		//	constructor
		//==========================================
		Mat3x3() : main() {}

		Mat3x3(const Mat3x3& other) : main(other.main) {}
		Mat3x3(const glm::mat3& other) : main(other) {}
		Mat3x3(const float& scalar) : main(scalar) {}

		Mat3x3(const float& a1, const float& a2, const float& a3,
			const float& a4, const float& a5, const float& a6,
			const float& a7, const float& a8, const float& a9) :
			main(a1, a2, a3, a4, a5, a6, a7, a8, a9) {}

		Mat3x3(const float ary[9]) :
			main(
			ary[0], ary[1], ary[2],
			ary[3], ary[4], ary[5],
			ary[6], ary[7], ary[8]
			) {}

		//==========================================
		//	method/operator
		//==========================================
		Mat3x3 Inverse() const
		{
			return glm::inverse(main);
		}

		float Determinant() const
		{
			return glm::determinant(main);
		}

		Mat3x3& operator=(const Mat3x3& other)
		{
			this->main = other.main;
			return *this;
		}

		operator glm::mat3() const
		{
			return main;
		}

		operator glm::mat3()
		{
			return main;
		}
	};

	//====================================================================================
	//	Mat4x4: Matric of float with 4 rows and 4 cols
	//====================================================================================
	struct Mat4x4
	{
		//==========================================
		//	memeber/variable
		//==========================================
		glm::mat4 main;

		//==========================================
		//	static method
		//==========================================
		static Mat4x4 Inverse(const Mat4x4& mat)
		{
			return mat.Inverse();
		}

		static float Determinant(const Mat4x4& mat)
		{
			return mat.Determinant();
		}

		//==========================================
		//	constructor
		//==========================================
		Mat4x4() : main() {}

		Mat4x4(const Mat4x4& other) : main(other.main) {}
		Mat4x4(const glm::mat4& other) : main(other) {}
		Mat4x4(const float& scalar) : main(scalar) {}

		Mat4x4(
			const float& a1, const float& a2, const float& a3, const float& a4,
			const float& a5, const float& a6, const float& a7, const float& a8,
			const float& a9, const float& a10, const float& a11, const float& a12,
			const float& a13, const float& a14, const float& a15, const float& a16) :
			main(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) {}

		Mat4x4(const float ary[16]) :
			main(
			ary[0], ary[1], ary[2], ary[3],
			ary[4], ary[5], ary[6], ary[7],
			ary[8], ary[9], ary[10], ary[11],
			ary[12], ary[13], ary[14], ary[15]
			) {}

		//==========================================
		//	method/operator
		//==========================================
		Mat4x4 Inverse() const
		{
			return glm::inverse(main);
		}

		float Determinant() const
		{
			return glm::determinant(main);
		}

		Mat4x4& operator=(const Mat4x4& other)
		{
			this->main = other.main;
			return *this;
		}

		operator glm::mat4() const
		{
			return main;
		}

		operator glm::mat4()
		{
			return main;
		}
	};

	//====================================================================================
	//	Quaternion: Core rotation presentation
	//====================================================================================
	struct Quaternion
	{
		//==========================================
		//	memeber/variable
		//==========================================
		glm::quat main;

		//==========================================
		//	static method
		//==========================================
		static Quaternion Identity()
		{
			return Quaternion();
		}

		static Vector3f EulerAngles(const Quaternion& q)
		{
			return q.GetEulerAngles();
		}

		static Quaternion Slerp(const Quaternion& lhs, const Quaternion& rhs, float value)
		{
			return glm::slerp(lhs.main, rhs.main, value);
		}

		static Quaternion RotationBetweenVectors(const Vector3f& from, const Vector3f to)
		{
			// TO DO:
		}
		//==========================================
		//	constructor
		//==========================================
		Quaternion() : main(glm::vec3(0, 0, 0)) {}
		Quaternion(const Quaternion& q) : main(q.main) {}
		Quaternion(const glm::quat& q) : main(q) {}
		Quaternion(Vector3f& euler)
		{
			glm::vec3 rad(glm::radians(euler.x()), glm::radians(euler.y()), glm::radians(euler.z()));
			main = glm::quat(rad);
		}

		Quaternion(const Mat3x3& _mat3)
		{
			main = glm::toQuat(glm::mat3(_mat3));
		}

		Quaternion(const Mat4x4& _mat4)
		{
			main = glm::toQuat(glm::mat4(_mat4));
		}

		//==========================================
		//	method/operator
		//==========================================

		Vector3f GetEulerAnglesInRad() const
		{
			return glm::eulerAngles(main);
		}

		void SetEulerAnglesInRad(const Vector3f& _euler)
		{
			main = glm::quat(_euler);
		}

		// return in degree
		Vector3f GetEulerAngles() const
		{
			return GetEulerAnglesInRad()/* * Math::Rad2Degf*/;
		}

		// set with degree
		void SetEulerAngles(const Vector3f& _euler)
		{
			SetEulerAnglesInRad(_euler/* * Math::Deg2Radf*/);
		}

		Mat4x4 GetMat3x3() const
		{
			return glm::toMat3(main);
		}

		Mat4x4 GetMat4x4() const
		{
			return glm::toMat4(main);
		}

		Quaternion& operator=(const Quaternion& other)
		{
			this->main = other.main;
			return *this;
		}
		
		Vector3f operator*(const Vector3f& vec) const
		{
			return glm::rotate(main, vec.main);
		}

		Quaternion operator*(const Quaternion& other) const
		{
			return main * other.main;
		}

		operator glm::quat() const 
		{ 
			return main; 
		}

		operator glm::quat()
		{
			return main;
		}
	};
}