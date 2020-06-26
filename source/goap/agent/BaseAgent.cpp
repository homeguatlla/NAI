#include "pch.h"
#include "BaseAgent.h"
#include "source/goap/IPredicate.h"

#include <cassert>

namespace NAI
{
	namespace Goap
	{
		BaseAgent::BaseAgent(std::shared_ptr<IGoapPlanner> goapPlanner, std::vector<std::shared_ptr<IPredicate>>& predicates) :
			mGoapPlanner{ goapPlanner },
			mPredicates{ predicates }
		{
			assert(goapPlanner);
			CreateStatesMachine();
		}

		void BaseAgent::Update(float elapsedTime)
		{
			mStatesMachine->Update(elapsedTime);
			mPredicates = mAgentContext->GetPredicates();
		}

		bool BaseAgent::HasPredicate(int predicateID) const
		{
			return std::find_if(mPredicates.begin(), mPredicates.end(), 
			[&predicateID](const std::shared_ptr<IPredicate> predicate)
			{
				return predicate->GetID() == predicateID;
			}) != mPredicates.end();
		}

		void BaseAgent::OnNewPredicate(std::shared_ptr<IPredicate> predicate)
		{
			if (!HasPredicate(predicate->GetID()))
			{
				mPredicates.push_back(predicate);
				NotifyNewPredicateToProcessState();
			}
		}

		void BaseAgent::NotifyNewPredicateToProcessState()
		{
			auto currentState = mStatesMachine->GetCurrentState();
			if (currentState->GetID() == AgentState::STATE_PROCESSING)
			{
				auto processingState = std::static_pointer_cast<Processing>(currentState);
				processingState->OnNewPredicate();
			}
		}

		AgentState BaseAgent::GetCurrentState() const
		{
			return mStatesMachine->GetCurrentState()->GetID();
		}

		void BaseAgent::CreateStatesMachine()
		{
			mAgentContext = std::make_shared<AgentContext>(mGoapPlanner, mPredicates);
			mStatesMachine = std::make_unique<core::utils::FSM::StatesMachine<AgentState, AgentContext>>(mAgentContext);

			auto planning = std::make_shared<Planning>();
			auto processing = std::make_shared<Processing>();

			mStatesMachine->AddState(planning);
			mStatesMachine->AddState(processing);

			//from Planning
			mStatesMachine->AddTransition(std::make_unique<EnterProcessing>(planning, processing));

			//from Processing
			mStatesMachine->AddTransition(std::make_unique<EnterPlanning>(processing, planning));

			mStatesMachine->SetInitialState(planning->GetID());
		}
	}
}
