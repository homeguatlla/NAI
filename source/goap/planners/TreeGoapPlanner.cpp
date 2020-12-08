#include "pch.h"
#include "TreeGoapPlanner.h"
#include "goap/IGoal.h"
#include "goap/IAction.h"
#include "goap/IPredicate.h"
#include "goap/GoapUtils.h"

namespace NAI
{
	namespace Goap
	{
		std::shared_ptr<IGoal> TreeGoapPlanner::GetPlan(std::vector<std::shared_ptr<IGoal>>& inputGoals, std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
		{
			if (!inputPredicates.empty() && !inputGoals.empty())
			{
				std::shared_ptr<IGoal> lessCostGoal = nullptr;
				unsigned int lessCost = std::numeric_limits<unsigned int>::max();
				std::vector<std::shared_ptr<IPredicate>> lessCostGoalPredicates;

				for (auto&& goal : inputGoals)
				{
					auto newPredicates = inputPredicates;
					bool satisfyGoalPreconditions = false;
					do 
					{
						auto predicatesAccomplished = goal->GetPredicatesSatisfyPreconditions(newPredicates);
						satisfyGoalPreconditions = !predicatesAccomplished.empty();

						if(satisfyGoalPreconditions)
						{
							auto cost = goal->GetCost(predicatesAccomplished);
							if(lessCostGoal == nullptr ||  cost < lessCost)
							{
								lessCost = cost;
								lessCostGoal = goal;
								lessCostGoalPredicates = predicatesAccomplished;
							}
							newPredicates = Utils::Substract(newPredicates, predicatesAccomplished);
						}
					} while(satisfyGoalPreconditions && !newPredicates.empty());
				}
				
				inputPredicates = Utils::Substract(inputPredicates, lessCostGoalPredicates);
				inputPredicates.insert(inputPredicates.begin(), lessCostGoalPredicates.begin(), lessCostGoalPredicates.end());

				return lessCostGoal;
			}

			return nullptr;
		}

		std::vector<std::shared_ptr<IGoal>> TreeGoapPlanner::GetPlanToReach(
			std::vector<std::shared_ptr<IGoal>>& inputGoals,
			std::vector<std::shared_ptr<IPredicate>>& inputPredicates,
			std::vector<std::shared_ptr<IPredicate>>& desiredPredicates) const
		{
			unsigned int bestCost = std::numeric_limits<unsigned int>::max();
			std::vector<std::shared_ptr<IGoal>> bestResult;
			bool isSolved = false;

			for (auto&& goal : inputGoals)
			{
				unsigned int totalCost = 0;
				std::vector<std::shared_ptr<IGoal>> result;

				auto predicatesAccomplished = goal->GetPredicatesCanBeAccomplished(desiredPredicates);
				if (!predicatesAccomplished.empty())
				{
					auto newDesiredPredicates = Utils::Substract(desiredPredicates, predicatesAccomplished);
					auto newInputPredicates = Utils::Concat(inputPredicates, predicatesAccomplished);

					auto newGoals = inputGoals;
					auto it = std::remove_if(newGoals.begin(), newGoals.end(), [&goal](std::shared_ptr<IGoal> g) { return g == goal; });
					newGoals.erase(it);
					result.push_back(goal);

					if(!newDesiredPredicates.empty())
					{	
						totalCost += goal->GetCost();

						auto newResult = GetPlanToReach(newGoals, newInputPredicates, newDesiredPredicates);
						if (newResult.empty())
						{
							//solution not found
							break;
						}
						else
						{
							isSolved = true;
							totalCost += UpdateGoalsResult(newResult, result);
						}
					}
					else
					{
						totalCost = result.empty() ? goal->GetCost() : totalCost + goal->GetCost();
						isSolved = true;
					}

					//save the best solution from the current best and the new one.
					if (isSolved && totalCost < bestCost)
					{
						bestCost = totalCost;
						bestResult = result;
					}
				}
			}

			return bestResult;
		}

		unsigned int TreeGoapPlanner::UpdateGoalsResult(
			std::vector<std::shared_ptr<IGoal>>& newResult, 
			std::vector<std::shared_ptr<IGoal>>& result) const
		{
			unsigned int cost = 0;
			for (auto plan : newResult)
			{
				cost += plan->GetCost();
			}
			result.insert(result.end(), newResult.begin(), newResult.end());

			return cost;
		}
	}
}