#include "pch.h"
#include "GoapPlanner.h"
#include "IGoal.h"
#include "IAction.h"
#include "IPredicate.h"


namespace NAI
{
	namespace Goap
	{
		std::shared_ptr<IGoal> GoapPlanner::GetPlan(std::vector<std::shared_ptr<IGoal>>& inputGoals, std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
		{
		//TODO este es el sistema a piñón. Habría que construir un árbol porque una acción se puede cumplir con distintos predicados.
		//por ejemplo el GoToGoal puede ser mejor ir al Saloon que al Herrero.
		//O atacar a un target puede ser con un cuchillo, o con una pistola.
		//Crear otro planner que construye el árbol de posibilidades.
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

		std::shared_ptr<IGoal> GoapPlanner::GetPlanToReach(
			std::vector<std::shared_ptr<IGoal>>& inputGoals,
			std::vector<std::shared_ptr<IPredicate>>& inputPredicates,
			std::vector<std::shared_ptr<IPredicate>>& desiredPredicates) const
		{
			return nullptr;
		}
	}
}