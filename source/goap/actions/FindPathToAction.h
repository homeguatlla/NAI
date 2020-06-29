#pragma once
#include "source/goap/BaseAction.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace NAI
{
	namespace Goap
	{
		class FindPathToAction : public BaseAction
		{
		public:
			FindPathToAction(
				const std::vector<std::shared_ptr<IPredicate>>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions);
			virtual ~FindPathToAction() = default;

			void Process(float elapsedTime) override;
		};
	}
}
