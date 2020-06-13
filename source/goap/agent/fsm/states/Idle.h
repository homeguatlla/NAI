#pragma once
#include "source/goap/agent/AgentContext.h"
#include "source/utils/fsm/BaseState.h"
#include "source/goap/types.h"

namespace NAI
{
	namespace Goap
	{
		class Idle : public core::utils::FSM::BaseState<AgentState, AgentContext>
		{
		public:
			Idle() = default;
			virtual ~Idle() = default;
			AgentState GetID() const override { return AgentState::STATE_IDLE; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
			void OnUpdate(float deltaTime) override;
		};
	}
}
