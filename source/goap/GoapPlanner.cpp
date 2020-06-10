#include "pch.h"
#include "GoapPlanner.h"
#include "Action.h"
#include "Predicate.h"

#include <algorithm>

namespace NAI
{
	std::vector<std::shared_ptr<Action>> GoapPlanner::GetPlan(const std::vector<std::shared_ptr<Action>>& actions, const std::vector<std::shared_ptr<Predicate>>& predicates) const
	{
		std::vector<std::shared_ptr<Action>> plan;

		if (!predicates.empty() && !actions.empty())
		{
			for (auto&& action : actions)
			{
				auto preconditions = action->GetPreconditions();
				if (SatifyPrecondition(preconditions, predicates))
				{
					plan.push_back(action);
				}
			}
		}

		return plan;
	}

	bool GoapPlanner::SatifyPrecondition(
		std::vector<std::shared_ptr<Predicate>>& preconditions, 
		std::vector<std::shared_ptr<Predicate>>& predicates) const
	{
		std::sort(preconditions.begin(), preconditions.end());
		std::sort(predicates.begin(), predicates.end());
		return std::includes(predicates.begin(), predicates.end(), preconditions.begin(), preconditions.end());
	}
}