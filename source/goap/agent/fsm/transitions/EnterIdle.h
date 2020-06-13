#pragma once
#include "source/utils/fsm/BaseTransition.h"
#include "source/goap/types.h"
#include "source/goap/agent/AgentContext.h"

namespace NAI
{
	namespace Goap
	{
		class EnterIdle : public core::utils::FSM::BaseTransition<AgentState, AgentContext>
		{
		public:
			EnterIdle(StatePtr origin, StatePtr destination);
			virtual ~EnterIdle() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
		};
	}
}
