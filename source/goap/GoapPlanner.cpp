#include "pch.h"
#include "GoapPlanner.h"
#include "IGoal.h"
#include "IAction.h"
#include "IPredicate.h"

#include <algorithm>

namespace NAI
{
	std::shared_ptr<IGoal> GoapPlanner::GetPlan(std::vector<std::shared_ptr<IGoal>>& inputGoals, std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
	{
		if (!inputPredicates.empty() && !inputGoals.empty())
		{
			std::shared_ptr<IGoal> lessCostGoal = nullptr;

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

	bool GoapPlanner::SatisfyActions(const std::vector<std::shared_ptr<IAction>>& inputActions, std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
	{
		bool satisfied = false;

		if (!inputPredicates.empty() && !inputActions.empty())
		{
			std::vector<std::shared_ptr<IPredicate>> predicates = inputPredicates;
			std::vector<std::shared_ptr<IAction>> actions = inputActions;			

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
		std::vector<std::shared_ptr<IPredicate>>& preconditions, 
		std::vector<std::shared_ptr<IPredicate>>& predicates) const
	{
		std::sort(preconditions.begin(), preconditions.end());
		std::sort(predicates.begin(), predicates.end());

		return std::includes(predicates.begin(), predicates.end(), preconditions.begin(), preconditions.end());
	}
}