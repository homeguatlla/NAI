#include "pch.h"
#include "AgentContext.h"

namespace NAI
{
	namespace Goap
	{
		AgentContext::AgentContext(std::shared_ptr<IGoapPlanner> planner, std::vector<std::shared_ptr<IPredicate>>& predicates) :
			mGoapPlanner{ planner },
			mCurrentPlan{ nullptr },
			mPredicates{ predicates }
		{
		}

		void AgentContext::SetPlan(std::shared_ptr<IGoal> plan)
		{
			mCurrentPlan = plan;
		}
	}
}