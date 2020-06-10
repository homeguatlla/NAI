#pragma once
#include <vector>
#include <memory>

namespace NAI
{
	class Action;
	class Predicate;

	class GoapPlanner
	{
	public:
		GoapPlanner() = default;
		~GoapPlanner() = default;

		std::vector<std::shared_ptr<Action>> GetPlan(
			const std::vector<std::shared_ptr<Action>>& actions, 
			const std::vector<std::shared_ptr<Predicate>>& predicates) const;

	private:
		bool SatifyPrecondition(
			std::vector<std::shared_ptr<Predicate>>& preconditions, 
			std::vector<std::shared_ptr<Predicate>>& predicates) const;
	};
}
