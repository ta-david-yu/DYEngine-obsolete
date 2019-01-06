#pragma once

#include "DYEngine/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

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
	//	Vector2f: 2 components float
	//====================================================================================
	struct DYE_API Vector2f
	{
		friend struct Vector3f;
		friend struct Vector4f;
		friend struct Mat2x2;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		glm::vec2 main;

	public:
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

		std::string ToString() const;

		float& operator[](int i);
		Vector2f& operator=(const Vector2f& other);
		Vector2f operator*(float scalar) const;
		Vector2f operator/(float scalar) const;
		bool operator==(const Vector2f& other) const;
		bool operator!=(const Vector2f& other) const;
		Vector2f operator+(const Vector2f& other) const;
		Vector2f operator-(const Vector2f& other) const;

		operator glm::vec2() const;
		operator glm::vec2();

		const float* GetValuePtr() const;
	};

	//====================================================================================
	//	Vector3f: 3 components float
	//====================================================================================
	struct DYE_API Vector3f
	{
		friend struct Vector4f;
		friend struct Mat3x3;
		friend struct Quaternion;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		glm::vec3 main;

	public:
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
		Mat4x4 ToTranslateMatrix() const;
		Mat4x4 ToScaleMatrix() const;
		Mat4x4 ToRotationMatrix() const;

		std::string ToString() const;

		float& operator[](int i);
		Vector3f& operator=(const Vector3f& other);
		Vector3f operator*(float scalar) const;
		Vector3f operator/(float scalar) const;
		bool operator==(const Vector3f& other) const;
		bool operator!=(const Vector3f& other) const;
		Vector3f operator+(const Vector3f& other) const;
		Vector3f operator-(const Vector3f& other) const;

		operator glm::vec3() const;
		operator glm::vec3();

		const float* GetValuePtr() const;
	};

	//====================================================================================
	//	Vector4f: 4 components float
	//====================================================================================
	struct DYE_API Vector4f
	{
		friend struct Mat4x4;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		glm::vec4 main;

	public:
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
		Vector4f(const Vector3f& vec, float w = 0);
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

		std::string ToString() const;

		float& operator[](int i);
		Vector4f& operator=(const Vector4f& other);
		Vector4f operator*(float scalar) const;
		Vector4f operator/(float scalar) const;
		bool operator==(const Vector4f& other) const;
		bool operator!=(const Vector4f& other) const;
		Vector4f operator+(const Vector4f& other) const;
		Vector4f operator-(const Vector4f& other) const;

		operator glm::vec4() const;
		operator glm::vec4();

		const float* GetValuePtr() const;
	};

	//====================================================================================
	//	Mat2x2: Matric of float with 2 rows and 2 cols
	//====================================================================================
	struct DYE_API Mat2x2
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		glm::mat2 main;

	public:
		//==========================================
		//	static method
		//==========================================
		static Mat2x2 Inverse(const Mat2x2& mat);

		static float Determinant(const Mat2x2& mat);

		//==========================================
		//	constructor
		//==========================================
		Mat2x2();
		Mat2x2(const Mat2x2& other);
		Mat2x2(const glm::mat2& other);
		Mat2x2(const float& scalar);
		Mat2x2(const float& a1, const float& a2,
			const float& a3, const float& a4);
		Mat2x2(const float ary[4]);

		//==========================================
		//	method/operator
		//==========================================
		Mat2x2 Transpose() const;

		Mat2x2 Inverse() const;

		float Determinant() const;

		Mat2x2& operator=(const Mat2x2& other);
		Mat2x2 operator*(const Mat2x2& other);
		Vector2f operator*(const Vector2f& other);

		operator glm::mat2() const;

		operator glm::mat2();

		//==========================================
		//	getter
		//==========================================
		const float* GetValuePtr() const;
	};

	//====================================================================================
	//	Mat3x3: Matric of float with 3 rows and 3 cols
	//====================================================================================
	struct DYE_API Mat3x3
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		glm::mat3 main;

	public:
		//==========================================
		//	static method
		//==========================================
		static Mat3x3 Inverse(const Mat3x3& mat);

		static float Determinant(const Mat3x3& mat);

		//==========================================
		//	constructor
		//==========================================
		Mat3x3();

		Mat3x3(const Mat3x3& other);
		Mat3x3(const glm::mat3& other);
		Mat3x3(const float& scalar);

		Mat3x3(const float& a1, const float& a2, const float& a3,
			const float& a4, const float& a5, const float& a6,
			const float& a7, const float& a8, const float& a9);

		Mat3x3(const float ary[9]);

		//==========================================
		//	method/operator
		//==========================================
		Mat3x3 Transpose() const;

		Mat3x3 Inverse() const;

		float Determinant() const;

		Mat3x3& operator=(const Mat3x3& other);
		Mat3x3 operator*(const Mat3x3& other);
		Vector3f operator*(const Vector3f& other);

		operator glm::mat3() const;

		operator glm::mat3();
		//==========================================
		//	getter
		//==========================================
		const float* GetValuePtr() const;

	};

	//====================================================================================
	//	Mat4x4: Matric of float with 4 rows and 4 cols
	//====================================================================================
	struct DYE_API Mat4x4
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		glm::mat4 main;

	public:
		//==========================================
		//	static method
		//==========================================
		static Mat4x4 Inverse(const Mat4x4& mat);
		static float Determinant(const Mat4x4& mat);

		//==========================================
		//	constructor
		//==========================================
		Mat4x4();

		Mat4x4(const Mat4x4& other);
		Mat4x4(const glm::mat4& other);
		Mat4x4(const float& scalar);

		Mat4x4(
			const float& a1, const float& a2, const float& a3, const float& a4,
			const float& a5, const float& a6, const float& a7, const float& a8,
			const float& a9, const float& a10, const float& a11, const float& a12,
			const float& a13, const float& a14, const float& a15, const float& a16);

		Mat4x4(const float ary[16]);

		//==========================================
		//	method/operator
		//==========================================
		Mat4x4 Transpose() const;

		Mat4x4 Inverse() const;

		float Determinant() const;

		Mat4x4& operator=(const Mat4x4& other);
		Mat4x4 operator*(const Mat4x4& other);
		Vector4f operator*(const Vector4f& other);


		operator glm::mat4() const;

		operator glm::mat4();

		//==========================================
		//	getter
		//==========================================
		const float* GetValuePtr() const;

	};

	//====================================================================================
	//	Quaternion: Core rotation presentation
	//====================================================================================
	struct DYE_API Quaternion
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		glm::quat main;

	public:
		//==========================================
		//	static method
		//==========================================
		static Quaternion Identity();

		static Vector3f EulerAngles(const Quaternion& q);

		static Quaternion Slerp(const Quaternion& lhs, const Quaternion& rhs, float value);

		static Quaternion RotationBetweenVectors(const Vector3f& from, const Vector3f to);
		//==========================================
		//	constructor
		//==========================================
		Quaternion();
		Quaternion(const Quaternion& q);
		Quaternion(const glm::quat& q);
		Quaternion(Vector3f& euler);
		Quaternion(const Mat3x3& _mat3);
		Quaternion(const Mat4x4& _mat4);

		//==========================================
		//	method/operator
		//==========================================

		Vector3f GetEulerAnglesInRad() const;

		void SetEulerAnglesInRad(const Vector3f& _euler);

		// return in degree
		Vector3f GetEulerAngles() const;

		// set with degree
		void SetEulerAngles(const Vector3f& _euler);

		Mat3x3 ToMat3x3() const;

		Mat4x4 ToMat4x4() const;

		Quaternion& operator=(const Quaternion& other);

		Vector3f operator*(const Vector3f& vec) const;

		Quaternion operator*(const Quaternion& other) const;

		operator glm::quat() const;

		operator glm::quat();
	};
}