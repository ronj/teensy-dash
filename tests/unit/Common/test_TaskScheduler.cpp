#include "yaffut.h"

#include "Common/Task.h"
#include "Common/TimedTask.h"
#include "Common/TaskScheduler.h"

// Not using hippomocks here since hippomocks won't call
// the constructor for us.
class TaskImpl : public Common::Task
{
public:
	virtual bool CanRun(uint32_t now) { return Runnable(now); }
	virtual void Run(uint32_t now) { OnRun(now); }
	std::function<bool(uint32_t)> Runnable;
	std::function<void(uint32_t)> OnRun;
};

class TimedTaskImpl : public Common::TimedTask
{
public:
	TimedTaskImpl(uint32_t now) : Common::TimedTask(now) {}
	virtual void Run(uint32_t now) { OnRun(now); }
	std::function<void(uint32_t)> OnRun;
};

struct TaskSchedulerTest
{
	static uint32_t GetTickCount() { static uint32_t ticks = 0; return ticks++; }

	TaskImpl taskA;
	TaskImpl taskB;
};

TEST(TaskSchedulerTest, should_run_task_when_runnable)
{
	Common::TaskScheduler scheduler;
	scheduler.GetMillisecondCount = TaskSchedulerTest::GetTickCount;

	scheduler.Add(taskA);
	scheduler.Add(taskB);

	taskA.Runnable = [](uint32_t now) { return now % 2 == 0; };
	taskB.Runnable = [](uint32_t now) { return now % 2 == 1; };

	taskA.OnRun = [](uint32_t now) { CHECK(now % 2 == 0); };
	taskB.OnRun = [](uint32_t now) { CHECK(now % 2 == 1); };

	for (int i = 0; i < 10; ++i)
	{
		scheduler.Run();
	}
}

TEST(TaskSchedulerTest, should_only_run_highest_priority_task)
{
	Common::TaskScheduler scheduler;
	scheduler.GetMillisecondCount = TaskSchedulerTest::GetTickCount;

	scheduler.Add(taskA);
	scheduler.Add(taskB);

	taskA.Runnable = [](uint32_t) { return true; };
	taskB.Runnable = [](uint32_t) { return true; };

	taskA.OnRun = [](uint32_t) { CHECK(true); };
	taskB.OnRun = [](uint32_t) { FAIL("Task should not be called"); };

	for (int i = 0; i < 10; ++i)
	{
		scheduler.Run();
	}
}

TEST(TaskSchedulerTest, should_run_timed_task_with_correct_interval)
{
	TimedTaskImpl timedTask(0);
	uint32_t ticks = 0;
	const uint32_t interval = 5;

	Common::TaskScheduler scheduler;
	scheduler.GetMillisecondCount = [& ticks]() { return ticks++; };

	scheduler.Add(timedTask);

	timedTask.OnRun = [&timedTask](uint32_t now) { CHECK(now % interval == 0); timedTask.IncrementRunTime(interval); };

	for (int i = 0; i < 50; ++i)
	{
		scheduler.Run();
	}
}
