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

			auto plan = GetContext()->GetPlan();
			mCurrentPlanActions = plan->GetActions();
			
			assert(!mCurrentPlanActions.empty());
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
			auto action = mCurrentPlanActions[0];
			mCurrentPlanActions.erase(mCurrentPlanActions.begin());

			bool satisfyPrecondition = action->SatisfyPrecondition(mPredicates);

			return satisfyPrecondition ? action : nullptr;

			/*int counter = mCurrentPlanActions.size();
			while (!satisfyPrecondition && counter > 0)
			{
				mCurrentPlanActions.push_back(action);

				action = mCurrentPlanActions[0];
				satisfyPrecondition = action->SatisfyPrecondition(mPredicates);

				mCurrentPlanActions.erase(mCurrentPlanActions.begin());

				counter--;
			}

			if (!satisfyPrecondition && counter == 0)
			{
				return nullptr;
			}
			else
			{
				return action;
			}*/
		}

		bool Processing::ThereAreActionsToProcess() const
		{
			return !mCurrentPlanActions.empty();
		}
	}
}