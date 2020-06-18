#include "pch.h"
#include "Planning.h"

namespace NAI
{
	namespace Goap
	{
		void Planning::OnInit()
		{

		}
		
		void Planning::OnEnter(float deltaTime)
		{

		}

		void Planning::OnUpdate(float deltaTime)
		{
			std::vector<std::shared_ptr<IGoal>> goals;
			std::vector<std::shared_ptr<IPredicate>> predicates;

			auto plan = mGoapPlanner.GetPlan(goals, predicates);
		}
	}
}