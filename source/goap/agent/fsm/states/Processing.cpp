#include "pch.h"
#include "Processing.h"
#include "source/goap/IGoal.h"
#include "source/goap/IAction.h"
#include "source/goap/GoapUtils.h"
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
			mPredicates = GetContext()->GetPredicates();
			mCurrentAction = GetNextActionToProcess();
		}

		void Processing::OnUpdate(float deltaTime)
		{
			if (!mCurrentAction)
			{
				Abort();
			}
			else if (!mCurrentAction->HasAccomplished())
			{
				mCurrentAction->Process(deltaTime);
			}
			else
			{
				AddActionPostConditionsToPredicatesList(mCurrentAction);

				if(ThereAreActionsToProcess())
				{ 
					mCurrentAction = GetNextActionToProcess();
				}
				else 
				{
					Accomplished();
				}
			}
		}

		void Processing::OnExit(float deltaTime)
		{
			auto plan = GetContext()->GetPlan();
			if (plan)
			{
				plan->Reset();
			}
			GetContext()->SetPlan(nullptr);
		}

		void Processing::OnPredicatesListChanged()
		{
			Abort();
		}

		void Processing::Accomplished()
		{
			auto plan = GetContext()->GetPlan();
			if (plan)
			{
				auto newPredicates = GetContext()->GetPredicates();
				plan->Accomplished(newPredicates);
				plan->Reset();
				GetContext()->SetPredicates(newPredicates);
			}
			GetContext()->SetPlan(nullptr);
		}

		void Processing::Abort()
		{
			auto plan = GetContext()->GetPlan();
			if (plan)
			{
				plan->Cancel();
				mCurrentAction = nullptr;
			}
			
			GetContext()->SetPlan(nullptr);
		}

		void Processing::AddActionPostConditionsToPredicatesList(std::shared_ptr<IAction> action)
		{
			auto postConditions = action->GetPostconditions();
			mPredicates = Utils::Concat(mPredicates, postConditions);
			GetContext()->SetPredicates(mPredicates);
		}

		std::shared_ptr<IAction> Processing::GetNextActionToProcess()
		{
			//After finish an action, the parent goal can add other actions to the list of actions
			//we need to ask and get the current plan everytime.
			auto plan = GetContext()->GetPlan();
			if (plan)
			{
				auto action = plan->GetNextAction();
				if(action)
				{
					bool satisfyPrecondition = action->SatisfyPrecondition(mPredicates);

					return satisfyPrecondition ? action : nullptr;
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				return nullptr;
			}
		}

		bool Processing::ThereAreActionsToProcess() const
		{
			auto plan = GetContext()->GetPlan();
			if(plan)
			{
				return plan->HasActions();
			}
			else
			{
				return false;
			}
		}
	}
}