#pragma once

#include <DYEngine\utilities\Vector.h>

namespace DYE
{
	//====================================================================================
	//	Rect
	//====================================================================================
	class Rect
	{
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		Vector2f m_Position;
		Vector2f m_Size;
		Vector2f m_Max;

		//==========================================
		//	method
		//==========================================
		//==========================================
		//	getter
		//==========================================
	public:
		Vector2f GetPosition() const;
		float GetX() const;
		float GetY() const;

		Vector2f GetSize() const;
		float GetWidth() const;
		float GetHeight() const;

		Vector2f GetMax() const;
		Vector2f GetMin() const;

		//==========================================
		//	setter
		//==========================================
	public:
		void SetPosition(const Vector2f& pos);
		void SetX(float x);
		void SetY(float y);

		void SetSize(const Vector2f& size);
		void SetWidth(float width);
		void SetHeight(float height);

		void SetMax(const Vector2f& max);
		void SetMin(const Vector2f& min);

		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		Rect();
		Rect(float x, float y, float width, float height);
		Rect(Vector2f pivot, Vector2f size);

		~Rect();
	};
}