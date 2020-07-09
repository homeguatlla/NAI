#include "pch.h"
#include "TreeGoapPlanner.h"
#include "source/goap/IGoal.h"
#include "source/goap/IAction.h"
#include "source/goap/IPredicate.h"
#include "source/goap/GoapUtils.h"

namespace NAI
{
	namespace Goap
	{
		std::shared_ptr<IGoal> TreeGoapPlanner::GetPlan(std::vector<std::shared_ptr<IGoal>>& inputGoals, std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
		{
			if (!inputPredicates.empty() && !inputGoals.empty())
			{
				std::shared_ptr<IGoal> lessCostGoal = nullptr;

				for (auto&& goal : inputGoals)
				{
					if (lessCostGoal == nullptr || goal->GetCost() < lessCostGoal->GetCost())
					{
						if (goal->SatisfyActions(inputPredicates))
						{
							lessCostGoal = goal;
						}
					}
				}

				return lessCostGoal;
			}

			return nullptr;
		}

		std::shared_ptr<IGoal> TreeGoapPlanner::GetPlanToReach(
			std::vector<std::shared_ptr<IGoal>>& inputGoals,
			std::vector<std::shared_ptr<IPredicate>>& inputPredicates,
			std::vector<std::shared_ptr<IPredicate>>& desiredPredicates) const
		{
			std::shared_ptr<IGoal> lessCostGoal = nullptr;

			for (auto&& goal : inputGoals)
			{
				auto predicatesAccomplished = goal->GetPredicatesCanBeAccomplished(desiredPredicates);
				if (!predicatesAccomplished.empty())
				{
					auto newDesiredPredicates = Utils::Substract(desiredPredicates, predicatesAccomplished);
					auto newInputPredicates = Utils::Concat(inputPredicates, predicatesAccomplished);

					auto newGoals = inputGoals;
					auto it = std::remove_if(newGoals.begin(), newGoals.end(), [&goal](std::shared_ptr<IGoal> g) { return g == goal; });
					newGoals.erase(it);
					if(!newDesiredPredicates.empty())
					{
						auto plan = GetPlanToReach(newGoals, newInputPredicates, newDesiredPredicates);
						if (lessCostGoal == nullptr || plan->GetCost() < lessCostGoal->GetCost())
						{
							lessCostGoal = plan;
						}
					}
					else
					{
						lessCostGoal = goal;
					}
				}
			}

			return lessCostGoal;
		}
	}
}