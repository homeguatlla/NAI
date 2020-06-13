#include "pch.h"
#include "EnterIdle.h"


namespace NAI
{
	namespace Goap
	{
		EnterIdle::EnterIdle(StatePtr origin, StatePtr destination) :
			core::utils::FSM::BaseTransition<AgentState, AgentContext>(origin, destination)
		{
		}

		void EnterIdle::OnInit()
		{
			
		}

		bool EnterIdle::CanPerformTransition() const
		{
			return true;
		}
	}
}