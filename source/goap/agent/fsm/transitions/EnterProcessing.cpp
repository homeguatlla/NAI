#include "pch.h"
#include "EnterProcessing.h"


namespace NAI
{
	namespace Goap
	{
		EnterProcessing::EnterProcessing(StatePtr origin, StatePtr destination) :
			core::utils::FSM::BaseTransition<AgentState, AgentContext>(origin, destination)
		{
		}

		void EnterProcessing::OnInit()
		{
			
		}

		bool EnterProcessing::CanPerformTransition() const
		{
			return GetContext()->HasPlan();
		}
	}
}