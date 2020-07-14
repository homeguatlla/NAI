#pragma once
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IGoal;
		class IPredicate;
		
		class IGoapPlanner
		{
		public:
			virtual ~IGoapPlanner() = default;

			virtual std::shared_ptr<IGoal> GetPlan(
				std::vector<std::shared_ptr<IGoal>>& inputGoals,
				std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const = 0;

			virtual std::vector<std::shared_ptr<IGoal>>  GetPlanToReach(
				std::vector<std::shared_ptr<IGoal>>& inputGoals,
				std::vector<std::shared_ptr<IPredicate>>& inputPredicates,
				std::vector<std::shared_ptr<IPredicate>>& desiredPredicates) const = 0;
		};
	}
}
