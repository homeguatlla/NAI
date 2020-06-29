#pragma once
#include "IGoapPlanner.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class GoapPlanner : public IGoapPlanner
		{
		public:
			GoapPlanner() = default;
			~GoapPlanner() = default;

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
