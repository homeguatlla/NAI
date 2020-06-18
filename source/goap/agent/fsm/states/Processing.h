#pragma once
#include "source/goap/agent/AgentContext.h"
#include "source/utils/fsm/BaseState.h"
#include "source/goap/GoapTypes.h"

namespace NAI
{
	namespace Goap
	{
		class Processing : public core::utils::FSM::BaseState<AgentState, AgentContext>
		{
		public:
			Processing() = default;
			virtual ~Processing() = default;
			AgentState GetID() const override { return AgentState::STATE_PROCESSING; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
			void OnUpdate(float deltaTime) override;
		};
	}
}
