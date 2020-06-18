#pragma once
#include "IAgent.h"
#include "AgentContext.h"
#include "source/goap/GoapTypes.h"
#include "source/utils/fsm/StatesMachine.h"
#include <vector>
#include <memory>


namespace NAI
{
	namespace Goap
	{
		class AgentContext;
		class IGoapPlanner;

		class BaseAgent : public IAgent
		{
		public:
			BaseAgent(std::shared_ptr<IGoapPlanner> goapPlanner);
			virtual ~BaseAgent() = default;

			AgentState GetCurrentState() const override;
			void Update(float elapsedTime) override;

		private:
			void CreateStatesMachine();

		private:
			std::unique_ptr<core::utils::FSM::StatesMachine<AgentState, AgentContext>> mStatesMachine;
			std::shared_ptr<AgentContext> mAgentContext;
			std::shared_ptr<IGoapPlanner> mGoapPlanner;
		};
	}
}

