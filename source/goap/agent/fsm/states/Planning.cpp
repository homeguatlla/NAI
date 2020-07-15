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
			auto predicates = GetContext()->GetPredicates();

			auto plan = mGoapPlanner->GetPlan(goals, predicates);
			if (plan)
			{
				//GetPlan, can change the order of the predicates putting the ones the goal needs to satisfy first
				//depending on cost. Then, we need to SetPredicates
				GetContext()->SetPredicates(predicates);
				GetContext()->SetPlan(plan);
			}
		}
	}
}