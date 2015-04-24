#pragma once

#include "Common/TimedTask.h"

namespace ApplicationLayer
{
	class ModelCollection;

	class ModelUpdateTask : public Common::TimedTask
	{
	public:
		ModelUpdateTask(ApplicationLayer::ModelCollection& models, uint32_t now);

		void Run(uint32_t now);

	private:
		ApplicationLayer::ModelCollection& m_Models;
	};
}
