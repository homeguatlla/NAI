#include "pch.h"
#include "BaseAgent.h"
#include "source/goap/agent/fsm/states/Planning.h"
#include "source/goap/agent/fsm/states/Processing.h"
#include "source/goap/agent/fsm/transitions/EnterPlanning.h"
#include "source/goap/agent/fsm/transitions/EnterProcessing.h"

namespace NAI
{
	namespace Goap
	{
		BaseAgent::BaseAgent()
		{
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
			mAgentContext = std::make_shared<AgentContext>();
			mStatesMachine = std::make_unique<core::utils::FSM::StatesMachine<AgentState, AgentContext>>(mAgentContext);

			auto planning = std::make_shared<Planning>();
			auto processing = std::make_shared<Processing>();
			
			mStatesMachine->AddState(planning);
			mStatesMachine->AddState(processing);

			//from Planning
			//mStatesMachine->AddTransition(std::make_unique<EnterWalk>(idle, walk));

			mStatesMachine->SetInitialState(planning->GetID());
		}
	}
}
