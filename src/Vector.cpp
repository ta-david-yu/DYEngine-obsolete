#include <DYEngine\utilities\Vector.h>
#include <DYEngine\utilities\Math.h>

namespace DYE
{
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
		return glm::length2(main);
	}

	Vector2f Vector2f::Normalized() const
	{
		return glm::normalize(main);
	}

	std::string Vector2f::ToString() const
	{
		return std::string("(" + std::to_string(main.x) + ", " + std::to_string(main.y) + ")");
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
		auto vec2bool = glm::epsilonEqual(this->main, other.main, Math::Elipsonf);
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

	const float* Vector2f::GetValuePtr() const
	{
		return glm::value_ptr<float>(main);
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
		return glm::length2(main);
	}

	Vector3f Vector3f::Normalized() const
	{
		return glm::normalize(main);
	}

	Mat4x4 Vector3f::ToTranslateMatrix() const
	{
		return glm::translate(main);
	}

	Mat4x4 Vector3f::ToScaleMatrix() const
	{
		return glm::scale(main);
	}

	Mat4x4 Vector3f::ToRotationMatrix() const
	{
		return glm::eulerAngleXYZ(main.x, main.y, main.z);
	}

	std::string Vector3f::ToString() const
	{
		return std::string("(" + std::to_string(main.x) + ", " + std::to_string(main.y) + ", " + std::to_string(main.z) + ")");
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
		auto vec3bool = glm::epsilonEqual(this->main, other.main, Math::Elipsonf);
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

	const float* Vector3f::GetValuePtr() const
	{
		return glm::value_ptr<float>(main);
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
	Vector4f::Vector4f(const Vector3f& vec, float w) : main(vec.main.x, vec.main.y, vec.main.z, w) {}
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
		return glm::length2(main);
	}

	Vector4f Vector4f::Normalized() const
	{
		return glm::normalize(main);
	}

	std::string Vector4f::ToString() const
	{
		return std::string("(" + std::to_string(main.x) + ", " + std::to_string(main.y) + ", " + std::to_string(main.z) + ", " + std::to_string(main.w) + ")");
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
		auto vec4bool = glm::epsilonEqual(this->main, other.main, Math::Elipsonf);
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

	const float* Vector4f::GetValuePtr() const
	{
		return glm::value_ptr<float>(main);
	}

	//====================================================================================
	//	Mat2x2: Matric of float with 2 rows and 2 cols
	//====================================================================================
	Mat2x2 Mat2x2::Inverse(const Mat2x2& mat)
	{
		return mat.Inverse();
	}

	float Mat2x2::Determinant(const Mat2x2& mat)
	{
		return mat.Determinant();
	}

	Mat2x2::Mat2x2() : main() {}
	Mat2x2::Mat2x2(const Mat2x2& other) : main(other.main) {}
	Mat2x2::Mat2x2(const glm::mat2& other) : main(other) {}
	Mat2x2::Mat2x2(const float& scalar) : main(scalar) {}
	Mat2x2::Mat2x2(const float& a1, const float& a2,
		const float& a3, const float& a4) : main(a1, a2, a3, a4) {}
	Mat2x2::Mat2x2(const float ary[4]) : main(ary[0], ary[1], ary[2], ary[3]) {}

	Mat2x2 Mat2x2::Transpose() const
	{
		return glm::transpose(main);
	}

	Mat2x2 Mat2x2::Inverse() const
	{
		return glm::inverse(main);
	}

	float Mat2x2::Determinant() const
	{
		return glm::determinant(main);
	}

	Mat2x2& Mat2x2::operator=(const Mat2x2& other)
	{
		this->main = other.main;
		return *this;
	}

	Mat2x2 Mat2x2::operator*(const Mat2x2& other)
	{
		return main * other.main;
	}

	Vector2f Mat2x2::operator*(const Vector2f& other)
	{
		return main * other.main;
	}


	Mat2x2::operator glm::mat2() const
	{
		return main;
	}

	Mat2x2::operator glm::mat2()
	{
		return main;
	}

	const float* Mat2x2::GetValuePtr() const
	{
		return glm::value_ptr<float>(main);
	}

	//====================================================================================
	//	Mat3x3: Matric of float with 3 rows and 3 cols
	//====================================================================================
	Mat3x3 Mat3x3::Inverse(const Mat3x3& mat)
	{
		return mat.Inverse();
	}

	float Mat3x3::Determinant(const Mat3x3& mat)
	{
		return mat.Determinant();
	}

	Mat3x3::Mat3x3() : main() {}

	Mat3x3::Mat3x3(const Mat3x3& other) : main(other.main) {}
	Mat3x3::Mat3x3(const glm::mat3& other) : main(other) {}
	Mat3x3::Mat3x3(const float& scalar) : main(scalar) {}

	Mat3x3::Mat3x3(const float& a1, const float& a2, const float& a3,
		const float& a4, const float& a5, const float& a6,
		const float& a7, const float& a8, const float& a9) :
		main(a1, a2, a3, a4, a5, a6, a7, a8, a9) {}

	Mat3x3::Mat3x3(const float ary[9]) :
		main(
			ary[0], ary[1], ary[2],
			ary[3], ary[4], ary[5],
			ary[6], ary[7], ary[8]
		) {}

	Mat3x3 Mat3x3::Transpose() const
	{
		return glm::transpose(main);
	}

	Mat3x3 Mat3x3::Inverse() const
	{
		return glm::inverse(main);
	}

	float Mat3x3::Determinant() const
	{
		return glm::determinant(main);
	}

	Mat3x3& Mat3x3::operator=(const Mat3x3& other)
	{
		this->main = other.main;
		return *this;
	}

	Mat3x3 Mat3x3::operator*(const Mat3x3& other)
	{
		return main * other.main;
	}

	Vector3f Mat3x3::operator*(const Vector3f& other)
	{
		return main * other.main;
	}

	Mat3x3::operator glm::mat3() const
	{
		return main;
	}

	Mat3x3::operator glm::mat3()
	{
		return main;
	}

	const float* Mat3x3::GetValuePtr() const
	{
		return glm::value_ptr<float>(main);
	}

	//====================================================================================
	//	Mat4x4: Matric of float with 4 rows and 4 cols
	//====================================================================================
	Mat4x4 Mat4x4::Inverse(const Mat4x4& mat)
	{
		return mat.Inverse();
	}

	float Mat4x4::Determinant(const Mat4x4& mat)
	{
		return mat.Determinant();
	}

	Mat4x4::Mat4x4() : main() {}

	Mat4x4::Mat4x4(const Mat4x4& other) : main(other.main) {}
	Mat4x4::Mat4x4(const glm::mat4& other) : main(other) {}
	Mat4x4::Mat4x4(const float& scalar) : main(scalar) {}

	Mat4x4::Mat4x4(
		const float& a1, const float& a2, const float& a3, const float& a4,
		const float& a5, const float& a6, const float& a7, const float& a8,
		const float& a9, const float& a10, const float& a11, const float& a12,
		const float& a13, const float& a14, const float& a15, const float& a16) :
		main(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) {}

	Mat4x4::Mat4x4(const float ary[16]) :
		main(
			ary[0], ary[1], ary[2], ary[3],
			ary[4], ary[5], ary[6], ary[7],
			ary[8], ary[9], ary[10], ary[11],
			ary[12], ary[13], ary[14], ary[15]
		) {}

	Mat4x4 Mat4x4::Transpose() const
	{
		return glm::transpose(main);
	}

	Mat4x4 Mat4x4::Inverse() const
	{
		return glm::inverse(main);
	}

	float Mat4x4::Determinant() const
	{
		return glm::determinant(main);
	}

	Mat4x4& Mat4x4::operator=(const Mat4x4& other)
	{
		this->main = other.main;
		return *this;
	}

	Mat4x4 Mat4x4::operator*(const Mat4x4& other)
	{
		return main * other.main;
	}

	Vector4f Mat4x4::operator*(const Vector4f& other)
	{
		return main * other.main;
	}

	Mat4x4::operator glm::mat4() const
	{
		return main;
	}

	Mat4x4::operator glm::mat4()
	{
		return main;
	}

	const float* Mat4x4::GetValuePtr() const
	{
		return glm::value_ptr<float>(main);
	}

	//====================================================================================
	//	Quaternion: Core rotation presentation
	//====================================================================================
	Quaternion Quaternion::Identity()
	{
		return Quaternion();
	}

	Vector3f Quaternion::EulerAngles(const Quaternion& q)
	{
		return q.GetEulerAngles();
	}

	Quaternion Quaternion::Slerp(const Quaternion& lhs, const Quaternion& rhs, float value)
	{
		return glm::slerp(lhs.main, rhs.main, value);
	}

	Quaternion Quaternion::RotationBetweenVectors(const Vector3f& from, const Vector3f to)
	{
		// TODO: implement
		return Quaternion();
	}

	Quaternion::Quaternion() : main(glm::vec3(0, 0, 0)) {}
	Quaternion::Quaternion(const Quaternion& q) : main(q.main) {}
	Quaternion::Quaternion(const glm::quat& q) : main(q) {}
	Quaternion::Quaternion(Vector3f& euler)
	{
		//glm::vec3 rad(glm::radians(euler.x()), glm::radians(euler.y()), glm::radians(euler.z()));
		//main = glm::quat(rad);
		SetEulerAngles(euler);
	}

	Quaternion::Quaternion(const Mat3x3& _mat3)
	{
		main = glm::toQuat(glm::mat3(_mat3));
	}

	Quaternion::Quaternion(const Mat4x4& _mat4)
	{
		main = glm::toQuat(glm::mat4(_mat4));
	}

	Vector3f Quaternion::GetEulerAnglesInRad() const
	{
		return glm::eulerAngles(main);
	}

	void Quaternion::SetEulerAnglesInRad(const Vector3f& _euler)
	{
		main = glm::quat(_euler);
	}

	Vector3f Quaternion::GetEulerAngles() const
	{
		return GetEulerAnglesInRad() * Math::Rad2Degf;
	}

	void Quaternion::SetEulerAngles(const Vector3f& _euler)
	{
		SetEulerAnglesInRad(_euler * Math::Deg2Radf);
	}

	Mat3x3 Quaternion::ToMat3x3() const
	{
		return glm::toMat3(main);
	}

	Mat4x4 Quaternion::ToMat4x4() const
	{
		return glm::toMat4(main);
	}

	Quaternion& Quaternion::operator=(const Quaternion& other)
	{
		this->main = other.main;
		return *this;
	}

	Vector3f Quaternion::operator*(const Vector3f& vec) const
	{
		return glm::rotate(main, vec.main);
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		return main * other.main;
	}

	Quaternion::operator glm::quat() const
	{
		return main;
	}

	Quaternion::operator glm::quat()
	{
		return main;
	}
}