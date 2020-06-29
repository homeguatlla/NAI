#include "pch.h"
#include "AgentContext.h"

namespace NAI
{
	namespace Goap
	{
		AgentContext::AgentContext(	std::shared_ptr<IGoapPlanner> planner, 
									std::vector<std::shared_ptr<IPredicate>>& predicates,
									std::vector<std::shared_ptr<IGoal>>& goals) :
			mGoapPlanner{ planner },
			mCurrentPlan{ nullptr },
			mPredicates{ predicates },
			mGoals { goals }
		{
		}

		void AgentContext::SetPlan(std::shared_ptr<IGoal> plan)
		{
			mCurrentPlan = plan;
		}
	}
}