#include "pch.h"
#include "Processing.h"
#include "source/goap/IGoal.h"
#include "source/goap/IAction.h"
#include <cassert>

namespace NAI
{
	namespace Goap
	{
		void Processing::OnInit()
		{

		}
		
		void Processing::OnEnter(float deltaTime)
		{
			auto plan = GetContext()->GetPlan();
			mCurrentPlanActions = plan->GetActions();
			
			assert(!mCurrentPlanActions.empty());
			mCurrentAction = GetNextActionToProcess();
		}

		void Processing::OnUpdate(float deltaTime)
		{
			if (!mCurrentAction->HasAccomplished())
			{
				mCurrentAction->Process(deltaTime);
			}
			else
			{
				if(ThereAreActionsToProcess())
				{ 
					mCurrentAction = GetNextActionToProcess();
				}
				else 
				{
					GetContext()->SetPlan(nullptr);
				}
			}
		}

		void Processing::OnExit(float deltaTime)
		{
			
		}

		std::shared_ptr<IAction> Processing::GetNextActionToProcess()
		{
			auto action = mCurrentPlanActions[0];
			mCurrentPlanActions.erase(mCurrentPlanActions.begin());

			return action;
		}

		bool Processing::ThereAreActionsToProcess() const
		{
			return !mCurrentPlanActions.empty();
		}
	}
}