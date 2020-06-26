#pragma once
#include "source/goap/GoapTypes.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IPredicate;

		class IAgent
		{
		public:
			virtual ~IAgent() = default;

			virtual void Update(float elapsedTime) = 0;
			virtual AgentState GetCurrentState() const = 0;
			virtual bool HasPredicate(int predicateID) const = 0;
			virtual void OnNewPredicate(std::shared_ptr<IPredicate> predicate) = 0;
		};
	}
}

