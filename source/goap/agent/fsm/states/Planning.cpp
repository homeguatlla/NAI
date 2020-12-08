#include "pch.h"
#include "Planning.h"
#include "source/goap/IGoapPlanner.h"

namespace NAI
{
	namespace Goap
	{
		void Planning::OnInit()
		{
			mGoapPlanner = GetContext()->GetGoapPlanner();
		}
		
		void Planning::OnEnter(float deltaTime)
		{
		}

		void Planning::OnUpdate(float deltaTime)
		{
			auto goals = GetContext()->GetGoals();
			auto predicatesHandler = GetContext()->GetPredicatesHandler();
			auto predicates = predicatesHandler.GetPredicatesList();

			const auto plan = mGoapPlanner->GetPlan(goals, predicates);
			if (plan)
			{
				//GetPlan, can change the order of the predicates putting the ones the goal needs to satisfy first
				//depending on cost. Then, we need to SetPredicatesHandler
				predicatesHandler.Reset(predicates);
				GetContext()->SetPredicatesHandler(predicatesHandler);
				GetContext()->SetPlan(plan);
			}
		}
	}
}