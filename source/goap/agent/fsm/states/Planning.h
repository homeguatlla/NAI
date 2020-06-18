#pragma once
#include "source/goap/agent/AgentContext.h"
#include "source/utils/fsm/BaseState.h"
#include "source/goap/GoapTypes.h"
#include "source/goap/GoapPlanner.h"

namespace NAI
{
	namespace Goap
	{
		class Planning : public core::utils::FSM::BaseState<AgentState, AgentContext>
		{
		public:
			Planning() = default;
			virtual ~Planning() = default;
			AgentState GetID() const override { return AgentState::STATE_PLANNING; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
			void OnUpdate(float deltaTime) override;

		private:
			GoapPlanner mGoapPlanner;
		};
	}
}
