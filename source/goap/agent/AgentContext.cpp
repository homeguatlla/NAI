#include "pch.h"
#include "AgentContext.h"

namespace NAI
{
	namespace Goap
	{
		AgentContext::AgentContext(std::shared_ptr<IGoapPlanner> planner) : 
		mGoapPlanner { planner },
		mCurrentPlan {nullptr}
		{
		}

		void AgentContext::SetPlan(std::shared_ptr<IGoal> plan)
		{
			mCurrentPlan = plan;
		}
	}
}