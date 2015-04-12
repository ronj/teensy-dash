#pragma once

#include "Platform.h"

namespace HardwareLayer
{
	class SDLPlatform : public Platform
	{
	public:
		virtual ~SDLPlatform();
		virtual void Init();
	};
}
