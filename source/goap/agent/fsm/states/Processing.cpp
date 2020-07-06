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
			
		}

		void Processing::OnPredicatesListChanged()
		{
			if (mCurrentAction != nullptr)
			{
				mCurrentAction->Cancel();
			}
			Abort();
		}

		void Processing::Accomplished()
		{
			GetContext()->SetPlan(nullptr);
		}

		void Processing::Abort()
		{
			mCurrentAction = nullptr;
			GetContext()->SetPlan(nullptr);
		}

		void Processing::AddActionPostConditionsToPredicatesList(std::shared_ptr<IAction> action)
		{
			auto postConditions = action->GetPostconditions();
			//TODO remove repeated predicates?
			mPredicates.insert(mPredicates.end(), postConditions.begin(), postConditions.end());
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

				bool satisfyPrecondition = action->SatisfyPrecondition(mPredicates);

				return satisfyPrecondition ? action : nullptr;

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