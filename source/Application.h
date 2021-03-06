#pragma once

#include "Version.h"

#include "Common/Logger.h"

class Application
{
public:
	int Run();

	void LogSoftwareVersion() const
	{
		Common::Logger::Get().Log("Software version: ", DASH_SOFTWARE_VERSION, '\n');
	}
};
