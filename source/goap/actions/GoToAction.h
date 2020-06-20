#pragma once
#include "source/goap/BaseAction.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace NAI
{
	namespace Goap
	{
		class GoToAction : public BaseAction
		{
		public:
			GoToAction(
				const std::vector<std::shared_ptr<IPredicate>>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions,
				glm::vec3 destination);
			virtual ~GoToAction() = default;

		private:
			glm::vec3 mDestination;
		};
	}
}
