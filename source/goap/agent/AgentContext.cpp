#include "pch.h"
#include "AgentContext.h"

namespace NAI
{
	namespace Goap
	{
		AgentContext::AgentContext(	std::shared_ptr<IGoapPlanner> planner, 
									const PredicatesHandler& predicatesHandler,
									std::vector<std::shared_ptr<IGoal>>& goals) :
			mGoapPlanner{ planner },
			mCurrentPlan{ nullptr },
			mPredicatesHandler{ predicatesHandler },
			mGoals { goals }
		{
		}

		void AgentContext::SetPlan(std::shared_ptr<IGoal> plan)
		{
			mCurrentPlan = plan;
		}
	}
}