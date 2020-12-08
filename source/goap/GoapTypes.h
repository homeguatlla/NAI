#pragma once
#include <map>
#include <string>

namespace NAI
{
	namespace Goap
	{
		const float MOVEMENT_PRECISION = 0.01f;
		
		enum class AgentState
		{
			STATE_PLANNING = 0,
			STATE_PROCESSING = 1,
		};

		static std::map<AgentState, std::string> AgentStateMap = {
			{ AgentState::STATE_PLANNING, std::string("Planning") },
			{ AgentState::STATE_PROCESSING, std::string("Processing") }
		};
	}
}

