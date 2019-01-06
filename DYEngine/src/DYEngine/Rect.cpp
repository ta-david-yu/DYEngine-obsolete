#include "DYEngine/math/Rect.h"

namespace DYE
{

	bool Rect::Contains(Vector2f& point) const
	{
		return (point.x() <= GetMax().x() && point.x() >= GetMin().x()) && (point.y() <= GetMax().y() && point.y() >= GetMin().y());
	}

	Vector2f Rect::GetPosition() const
	{
		return m_Position;
	}

	float Rect::GetX() const { return GetPosition().x(); }
	float Rect::GetY() const { return GetPosition().y(); }

	Vector2f Rect::GetSize() const
	{
		return m_Size;
	}

	float Rect::GetWidth() const { return GetSize().x(); }
	float Rect::GetHeight() const { return GetSize().y(); }

	Vector2f Rect::GetMax() const
	{
		return m_Max;
	}

	Vector2f Rect::GetMin() const
	{
		return m_Position;
	}

	Vector2f Rect::GetCenter() const
	{
		return (GetMax() + GetMin()) / 2.0f;
	}

	void Rect::SetPosition(const Vector2f& pos)
	{
		// calculate Max and Min
		m_Position = pos;
		m_Max = m_Position + m_Size;
	}

	void Rect::SetX(float x) { SetPosition(Vector2f(x, GetPosition().y())); }

	void Rect::SetY(float y) { SetPosition(Vector2f(GetPosition().x(), y)); }

	void Rect::SetSize(const Vector2f& size)
	{
		// calculate Max and Min
		m_Size = size;
		m_Max = m_Position + m_Size;
	}

	void Rect::SetWidth(float width) { SetSize(Vector2f(width, GetSize().y())); }

	void Rect::SetHeight(float height) { SetSize(Vector2f(GetSize().x(), height)); }

	void Rect::SetMax(const Vector2f& max)
	{
		// calculate Position and Size
		m_Max = max;
		m_Size = m_Max - m_Position;
	}

	void Rect::SetMin(const Vector2f& min)
	{
		// calculate Position and Size
		m_Position = min;
		m_Size = m_Max - m_Position;
	}

	Rect::Rect()
	{
		SetPosition(Vector2f(0, 0));
		SetSize(Vector2f(0, 0));
	}

	Rect::Rect(const Rect& rect)
	{
		SetPosition(rect.GetPosition());
		SetSize(rect.GetSize());
	}

	Rect::Rect(float x, float y, float width, float height)
	{
		SetPosition(Vector2f(x, y));
		SetSize(Vector2f(width, height));
	}

	Rect::Rect(Vector2f pivot, Vector2f size)
	{
		SetPosition(pivot);
		SetSize(size);
	}

	Rect::~Rect()
	{

	}
}