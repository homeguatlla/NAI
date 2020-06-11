#pragma once
#include <vector>
#include <memory>

namespace NAI
{
	class Goal;
	class Predicate;
	class Action;

	class GoapPlanner
	{
	public:
		GoapPlanner() = default;
		~GoapPlanner() = default;

		std::shared_ptr<Goal> GetPlan(
			std::vector<std::shared_ptr<Goal>>& inputGoals, 
			std::vector<std::shared_ptr<Predicate>>& inputPredicates) const;

	private:
		bool SatisfyActions(
			const std::vector<std::shared_ptr<Action>>& inputActions,
			std::vector<std::shared_ptr<Predicate>>& inputPredicates) const;

		bool SatisfyPrecondition(
			std::vector<std::shared_ptr<Predicate>>& preconditions, 
			std::vector<std::shared_ptr<Predicate>>& predicates) const;
	};
}
