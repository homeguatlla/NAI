#include "pch.h"
#include "DirectGoapPlanner.h"
#include "goap/IGoal.h"
#include "goap/IAction.h"
#include "goap/IPredicate.h"
#include "goap/GoapUtils.h"

namespace NAI
{
	namespace Goap
	{
		std::shared_ptr<IGoal> DirectGoapPlanner::GetPlan(std::vector<std::shared_ptr<IGoal>>& inputGoals, std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
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

		std::vector<std::shared_ptr<IGoal>> DirectGoapPlanner::GetPlanToReach(
			std::vector<std::shared_ptr<IGoal>>& inputGoals,
			std::vector<std::shared_ptr<IPredicate>>& inputPredicates,
			std::vector<std::shared_ptr<IPredicate>>& desiredPredicates) const
		{
			std::vector<std::shared_ptr<IGoal>> bestResult;

			return bestResult;
		}
	}
}