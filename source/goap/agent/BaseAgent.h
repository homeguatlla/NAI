#pragma once
#include "IAgent.h"
#include "AgentContext.h"
#include "../types.h"
#include "../../utils/fsm/StatesMachine.h"
#include <vector>
#include <memory>


namespace NAI
{
	namespace Goap
	{
		class AgentContext;

		class BaseAgent : public IAgent
		{
		public:
			BaseAgent();
			virtual ~BaseAgent() = default;

			AgentState GetCurrentState() const override;
			void Update(float elapsedTime) override;

		private:
			void CreateStatesMachine();

		private:
			std::unique_ptr<core::utils::FSM::StatesMachine<AgentState, AgentContext>> mStatesMachine;
			std::shared_ptr<AgentContext> mAgentContext;
		};
	}
}

