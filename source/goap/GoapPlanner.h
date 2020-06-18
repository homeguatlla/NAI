#pragma once
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IGoal;
		class IPredicate;
		class IAction;

		class GoapPlanner
		{
		public:
			GoapPlanner() = default;
			~GoapPlanner() = default;

			std::shared_ptr<IGoal> GetPlan(
				std::vector<std::shared_ptr<IGoal>>& inputGoals,
				std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const;
			bool GetTest() const { return 1; }
		private:
			bool SatisfyActions(
				const std::vector<std::shared_ptr<IAction>>& inputActions,
				std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const;

			bool SatisfyPrecondition(
				std::vector<std::shared_ptr<IPredicate>>& preconditions,
				std::vector<std::shared_ptr<IPredicate>>& predicates) const;
		};
	}
}
