#pragma once

#include "Common/Task.h"

namespace ApplicationLayer
{
	class ModelCollection;

	class ModelUpdateTask : public Common::Task
	{
	public:
		ModelUpdateTask(ApplicationLayer::ModelCollection& models);

		bool CanRun(uint32_t) { return true; }
		void Run(uint32_t now);

	private:
		ApplicationLayer::ModelCollection& m_Models;
	};
}
