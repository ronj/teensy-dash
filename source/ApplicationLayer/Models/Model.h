#pragma once

#include "Common/List.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class Model : public Common::List<Model>::Element
		{
		public:
			virtual int32_t GetRawValue() const = 0;
			virtual const char* GetFormattedValue() const = 0;
			virtual void Update() = 0;

		protected:
			Model();
		};
	}
}
