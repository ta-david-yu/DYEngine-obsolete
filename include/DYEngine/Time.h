#pragma once

#include <DYEngine\Main.h>

namespace DYE
{
	class Time
	{
		static float unScaledDeltaTime;

		static float unScaledFixedDeltaTime;

		static float realTimeSinceStart;

		static float scale;

		static float DeltaTime() { return scale * unScaledDeltaTime; }

		static float FixedDeltaTime() { return scale * unScaledFixedDeltaTime; }
	};


}