#pragma once
#include "IAgent.h"
#include <vector>
#include <memory>

namespace core
{
	namespace utils
	{
		namespace FSM
		{
			class StatesMachine;
		}
	}
}

namespace NAI
{
	namespace Goap
	{
		class BaseAgent : public IAgent
		{
		public:
			BaseAgent() = default;
			virtual ~BaseAgent() = default;

		private:
			core::utils::FSM::StatesMachine<AgentState,  mStatesMachine;
		};
	}
}

