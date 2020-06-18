#include "pch.h"
#include "EnterPlanning.h"


namespace NAI
{
	namespace Goap
	{
		EnterPlanning::EnterPlanning(StatePtr origin, StatePtr destination) :
			core::utils::FSM::BaseTransition<AgentState, AgentContext>(origin, destination)
		{
		}

		void EnterPlanning::OnInit()
		{
			
		}

		bool EnterPlanning::CanPerformTransition() const
		{
			return true;
		}
	}
}