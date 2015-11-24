#pragma once

#include "Model.h"

namespace ApplicationLayer
{
	namespace Models
	{
		class RepresentableModel : public Model
		{
		public:
			virtual const char* GetFormattedValue() const = 0;
		};
	}
}
