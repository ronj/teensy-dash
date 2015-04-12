#pragma once

#include "Model.h"

namespace ApplicationLayer
{
	namespace Models
	{
		class RandomValueModel : public Model
		{
		public:
			RandomValueModel(int32_t from, int32_t to);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update();

		private:
			int32_t m_Value;
			int32_t m_From;
			int32_t m_To;
		};
	}
}
