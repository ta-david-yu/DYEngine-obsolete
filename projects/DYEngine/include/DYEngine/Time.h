#pragma once

#include <DYEngine/Core.h>

#include <DYEngine/interfaces/IApplication.h>

#include <chrono>
#include <thread>
#include <ctime>

#define TIME DYE::Time::GetInstance()

namespace DYE
{
	//====================================================================================
	//	Time: global Time updator
	//====================================================================================
	class DYE_API Time
	{
		friend class IApplication;

		using TimePoint =
			std::chrono::steady_clock::time_point;
			// std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>>;

		using TimeDuration =
			std::chrono::duration<double>;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static Time* s_pInstance;

		double m_UnScaledDeltaTime;
		double m_UnScaledFixedDeltaTime;

		double m_RealTimeSinceStart = 0.0f;
		double m_TimeScale = 1.0f;

		//==========================================
		//	state
		//==========================================
		TimePoint m_frameStartTimePoint;
		TimeDuration m_deltaDuration;

		//==========================================
		//	procedure
		//==========================================
		void tickInit(float dt = 1.0f / 60.0f, float fixedDt = 1.0f / 60.0f);
		void tickUpdate();

		//==========================================
		//	method
		//==========================================
		double frameDuration() const;

	public:
		static Time* GetInstance();

		float DeltaTime() const;

		float FixedDeltaTime() const;

		float UnScaled_DeltaTime() const;

		float UnScaled_FixedDeltaTime() const;

		void SetTimeScale(float _scale);

		std::string GetDateString() const;	// TODO: implement a date struct
	};
}