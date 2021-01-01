#include "pch.h"
#include "PerceptionSystem.h"
#include <goap/agent/IAgent.h>

namespace NAI
{
	namespace Goap
	{
		PerceptionSystem::PerceptionSystem()
		{
		}

		void PerceptionSystem::Update(
			float elapsedTime,
			Memory<IStimulus>& memory,
			std::shared_ptr<IAgent> agent)
		{
			memory.PerformActionForEach(
				[agent](std::shared_ptr<IStimulus> stimulus)
				{
					const auto newPredicatesList = agent->Evaluate(stimulus);
					if(!newPredicatesList.empty())
					{
						//TODO we can evaluate each predicate to really see if we must add it or not into the
						//predicates list of the agent.
						for(auto&& predicate : newPredicatesList)
						{
							agent->OnNewPredicate(predicate);
						}
					}
				});
			
		}
	}
}
