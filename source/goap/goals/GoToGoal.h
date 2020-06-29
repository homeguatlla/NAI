#pragma once
#include "source/goap/BaseGoal.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace NAI
{
	namespace Goap
	{
		class GoToGoal : public BaseGoal
		{
		public:
			GoToGoal();
			virtual ~GoToGoal() = default;

		private:
			std::shared_ptr<IAction> CreateFollowPathAction();
			std::shared_ptr<IAction> CreateFindPathToAction();

		private:
			glm::vec3 mDestination;
		};
	}
}
