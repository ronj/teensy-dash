#include "ModelUpdateTask.h"

#include "ModelCollection.h"
#include "Models/Model.h"

ApplicationLayer::ModelUpdateTask::ModelUpdateTask(ApplicationLayer::ModelCollection& models, uint32_t now)
	: TimedTask(now)
	, m_Models(models)
{
}

void ApplicationLayer::ModelUpdateTask::Run(uint32_t now)
{
	for (auto&& model : m_Models.GetModels())
	{
		model.Update(now);
	}

	IncrementRunTime(50);
}
