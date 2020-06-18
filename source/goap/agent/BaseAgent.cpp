#include "pch.h"
#include "BaseAgent.h"
#include "source/goap/agent/fsm/states/Planning.h"
#include "source/goap/agent/fsm/states/Processing.h"
#include "source/goap/agent/fsm/transitions/EnterPlanning.h"
#include "source/goap/agent/fsm/transitions/EnterProcessing.h"
#include <cassert>

namespace NAI
{
	namespace Goap
	{
		BaseAgent::BaseAgent(std::shared_ptr<IGoapPlanner> goapPlanner) :
		mGoapPlanner {goapPlanner}
		{
			assert(goapPlanner);
			CreateStatesMachine();
		}

		void BaseAgent::Update(float elapsedTime)
		{
			mStatesMachine->Update(elapsedTime);
		}

		AgentState BaseAgent::GetCurrentState() const
		{
			return mStatesMachine->GetCurrentState()->GetID();
		}


		void BaseAgent::CreateStatesMachine()
		{
			mAgentContext = std::make_shared<AgentContext>(mGoapPlanner);
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
