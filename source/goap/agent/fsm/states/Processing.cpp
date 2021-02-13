#include "pch.h"
#include "Processing.h"
#include "goap/IGoal.h"
#include "goap/IAction.h"
#include "goap/GoapUtils.h"
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
			mPredicatesHandler = GetContext()->GetPredicatesHandler();
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
				auto& newPredicates = mPredicatesHandler.GetPredicatesList();
				plan->Reset(newPredicates);
				mPredicatesHandler.Reset(newPredicates);
				GetContext()->SetPredicatesHandler(mPredicatesHandler);
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
				auto& newPredicates = mPredicatesHandler.GetPredicatesList();
				plan->Accomplished(newPredicates);
				plan->Reset(newPredicates);
				mPredicatesHandler.Reset(newPredicates);
				GetContext()->SetPredicatesHandler(mPredicatesHandler);
			}
			GetContext()->SetPlan(nullptr);
		}

		void Processing::Abort()
		{
			//we should update the predicates handler if abort is because a new predicate.
			mPredicatesHandler = GetContext()->GetPredicatesHandler();
			auto plan = GetContext()->GetPlan();
			if (plan)
			{
				auto& newPredicates = mPredicatesHandler.GetPredicatesList();
				plan->Cancel(newPredicates);
				mPredicatesHandler.Reset(newPredicates);
				GetContext()->SetPredicatesHandler(mPredicatesHandler);
				mCurrentAction = nullptr;
			}
			
			GetContext()->SetPlan(nullptr);
		}

		void Processing::AddActionPostConditionsToPredicatesList(std::shared_ptr<IAction> action)
		{
			const auto postConditions = action->GetPostconditions();
			const auto resultPredicates = Utils::Concat(mPredicatesHandler.GetPredicatesList(), postConditions);
			mPredicatesHandler.Reset(resultPredicates);
			GetContext()->SetPredicatesHandler(mPredicatesHandler);
		}

		std::shared_ptr<IAction> Processing::GetNextActionToProcess() const
		{
			//After finish an action, the parent goal can add other actions to the list of actions
			//we need to ask and get the current plan everytime.
			auto plan = GetContext()->GetPlan();
			if (plan)
			{
				auto action = plan->GetNextAction();
				if(action)
				{
					const auto satisfyPrecondition = action->SatisfyPrecondition(mPredicatesHandler.GetPredicatesList());

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
			const auto plan = GetContext()->GetPlan();
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