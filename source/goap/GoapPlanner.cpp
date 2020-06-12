#include "pch.h"
#include "GoapPlanner.h"
#include "Goal.h"
#include "Action.h"
#include "Predicate.h"

#include <algorithm>

namespace NAI
{
	std::shared_ptr<Goal> GoapPlanner::GetPlan(std::vector<std::shared_ptr<Goal>>& inputGoals, std::vector<std::shared_ptr<Predicate>>& inputPredicates) const
	{
		if (!inputPredicates.empty() && !inputGoals.empty())
		{
			std::shared_ptr<Goal> lessCostGoal = nullptr;

			for (auto&& goal : inputGoals)
			{
				if (lessCostGoal == nullptr || goal->GetCost() < lessCostGoal->GetCost())
				{
					if (SatisfyActions(goal->GetActions(), inputPredicates))
					{

						lessCostGoal = goal;
					}
				}
			}

			return lessCostGoal;
		}

		return {};
	}

	bool GoapPlanner::SatisfyActions(const std::vector<std::shared_ptr<Action>>& inputActions, std::vector<std::shared_ptr<Predicate>>& inputPredicates) const
	{
		bool satisfied = false;

		if (!inputPredicates.empty() && !inputActions.empty())
		{
			std::vector<std::shared_ptr<Predicate>> predicates = inputPredicates;
			std::vector<std::shared_ptr<Action>> actions = inputActions;			

			int lastPredicatesSize = predicates.size();
			do
			{
				lastPredicatesSize = predicates.size();
				for (auto it = actions.begin(); it != actions.end();)
				{
					auto action = *it;
					auto preconditions = action->GetPreconditions();
					if (SatisfyPrecondition(preconditions, predicates))
					{
						auto postconditions = action->GetPostconditions();
						predicates.insert(end(predicates), begin(postconditions), end(postconditions));
						it = actions.erase(it);
					}
					else
					{
						it++;
					}
				}
			} while (static_cast<int>(predicates.size()) > lastPredicatesSize);

			satisfied = actions.empty();
		}

		return satisfied;
	}

	bool GoapPlanner::SatisfyPrecondition(
		std::vector<std::shared_ptr<Predicate>>& preconditions, 
		std::vector<std::shared_ptr<Predicate>>& predicates) const
	{
		std::sort(preconditions.begin(), preconditions.end());
		std::sort(predicates.begin(), predicates.end());
		return std::includes(predicates.begin(), predicates.end(), preconditions.begin(), preconditions.end());
	}
}