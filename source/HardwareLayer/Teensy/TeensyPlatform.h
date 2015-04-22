#pragma once

#include "Platform.h"

namespace HardwareLayer
{
	class TeensyPlatform : public Platform
	{
	public:
		TeensyPlatform();
		virtual ~TeensyPlatform();

		virtual void Init();

	private:
		void LogResetReason() const;
	};
}
