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
			virtual void Update(uint32_t now) = 0;

		protected:
			Model();
		};
	}
}
