#pragma once
#include "utils/fsm/BaseTransition.h"
#include "goap/GoapTypes.h"
#include "goap/agent/AgentContext.h"

namespace NAI
{
	namespace Goap
	{
		class EnterPlanning : public core::utils::FSM::BaseTransition<AgentState, AgentContext>
		{
		public:
			EnterPlanning(StatePtr origin, StatePtr destination);
			virtual ~EnterPlanning() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
		};
	}
}
