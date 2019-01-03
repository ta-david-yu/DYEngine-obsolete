#include <DYEngine/Time.h>

#include <DYEngine/utilities/Logger.h>

namespace DYE
{
	Time* Time::s_pInstance = nullptr;

	Time* Time::GetInstance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new Time();

		DYE_ASSERT(s_pInstance != nullptr, "Instance not found.");
		return s_pInstance;
	}

	void Time::tickInit(float dt, float fixedDt)
	{
		m_UnScaledDeltaTime = dt;
		m_UnScaledFixedDeltaTime = fixedDt;

		m_RealTimeSinceStart = 0.0f;
		m_TimeScale = 1.0f;

		m_deltaDuration = TimeDuration(dt);

		m_frameStartTimePoint = std::chrono::steady_clock::now();
	}

	void Time::tickUpdate()
	{	
		TimePoint now(std::chrono::steady_clock::now());

		m_deltaDuration = now - m_frameStartTimePoint;

		m_RealTimeSinceStart += m_deltaDuration.count();
		m_UnScaledDeltaTime = m_deltaDuration.count();

		m_frameStartTimePoint = now;
		
	}

	double Time::frameDuration() const { return m_deltaDuration.count(); }

	float Time::DeltaTime() const 
	{ 
		return (float)(m_TimeScale * m_UnScaledDeltaTime); 
	}

	float Time::FixedDeltaTime() const 
	{ 
		return (float)(m_TimeScale * m_UnScaledFixedDeltaTime);
	}

	float Time::UnScaled_DeltaTime() const
	{ 
		return (float) m_UnScaledDeltaTime; 
	}

	float Time::UnScaled_FixedDeltaTime() const
	{ 
		return (float) m_UnScaledFixedDeltaTime; 
	}

	void Time::SetTimeScale(float _scale) 
	{ 
		m_TimeScale = _scale; 
	}

	std::string Time::GetDateString() const
	{
		auto now = std::chrono::system_clock::now();
		std::time_t now_t = std::chrono::system_clock::to_time_t(now);
		return std::string(std::ctime(&now_t));
	}
}