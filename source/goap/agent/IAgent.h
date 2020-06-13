#pragma once

#include "source/goap/types.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IAgent
		{
		public:
			virtual ~IAgent() = default;

			virtual void Update(float elapsedTime) = 0;
			virtual AgentState GetCurrentState() const = 0;
		};
	}
}

