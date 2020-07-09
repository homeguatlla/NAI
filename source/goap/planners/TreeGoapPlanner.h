#pragma once
#include "source/goap/IGoapPlanner.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class TreeGoapPlanner : public IGoapPlanner
		{
		public:
			TreeGoapPlanner() = default;
			~TreeGoapPlanner() = default;

			std::shared_ptr<IGoal> GetPlan(
				std::vector<std::shared_ptr<IGoal>>& inputGoals,
				std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const override;

			std::shared_ptr<IGoal> GetPlanToReach(
				std::vector<std::shared_ptr<IGoal>>& inputGoals,
				std::vector<std::shared_ptr<IPredicate>>& inputPredicates,
				std::vector<std::shared_ptr<IPredicate>>& desiredPredicates) const override;
		};
	}
}
