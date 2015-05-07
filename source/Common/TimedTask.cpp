#include "TimedTask.h"

Common::TimedTask::TimedTask(uint32_t when)
	: m_Runtime(when)
{
}

bool Common::TimedTask::CanRun(uint32_t now)
{
	return now >= m_Runtime;
}

void Common::TimedTask::SetRunTime(uint32_t when)
{
	m_Runtime = when;
}

void Common::TimedTask::IncrementRunTime(uint32_t inc)
{
	m_Runtime += inc;
}
