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
				GetContext()->SetPlan(plan);
			}
		}
	}
}