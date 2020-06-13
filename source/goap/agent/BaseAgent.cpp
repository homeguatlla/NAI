#include "pch.h"
#include "BaseAgent.h"
#include "source/goap/agent/fsm/states/Idle.h"
#include "source/goap/agent/fsm/transitions/EnterIdle.h"

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

			auto idle = std::make_shared<Idle>();
			
			mStatesMachine->AddState(idle);


			//from Idle
			//mStatesMachine->AddTransition(std::make_unique<EnterWalk>(idle, walk));

			mStatesMachine->SetInitialState(idle->GetID());
		}
	}
}
