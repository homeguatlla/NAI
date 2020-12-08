#pragma once
#include "utils/fsm/BaseTransition.h"
#include "goap/GoapTypes.h"
#include "goap/agent/AgentContext.h"

namespace NAI
{
	namespace Goap
	{
		class EnterProcessing : public core::utils::FSM::BaseTransition<AgentState, AgentContext>
		{
		public:
			EnterProcessing(StatePtr origin, StatePtr destination);
			virtual ~EnterProcessing() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
		};
	}
}
