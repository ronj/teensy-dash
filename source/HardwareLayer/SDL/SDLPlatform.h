#pragma once

#include "Platform.h"

namespace HardwareLayer
{
	class SDLPlatform : public Platform
	{
	public:
		SDLPlatform();
		virtual ~SDLPlatform();

		virtual void Init();
	};
}
