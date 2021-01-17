#include "pch.h"
#include "CognitiveSystem.h"

#include <goap/agent/IAgent.h>

namespace NAI
{
    namespace Goap
    {
        void CognitiveSystem::Update(
            float elapsedTime,
            Memory<IStimulus>& memory,
            std::shared_ptr<IAgent> agent)
        {
            const auto newPredicatesList = agent->TransformStimulusIntoPredicates(memory);
            if(!newPredicatesList.empty())
            {
                //TODO we can evaluate each predicate to really see if we must add it or not into the
                //predicates list of the agent.
                for(auto&& predicate : newPredicatesList)
                {
                    agent->OnNewPredicate(predicate);
                }
            }
            /*
            memory.PerformActionForEach(
                [agent](std::shared_ptr<IStimulus> stimulus)
                {
                    if(agent->IsStimulusAccepted(stimulus))
                    {
                        const auto newPredicatesList = agent->TransformStimulusIntoPredicates(stimulus);
                        if(!newPredicatesList.empty())
                        {
                            //TODO we can evaluate each predicate to really see if we must add it or not into the
                            //predicates list of the agent.
                            for(auto&& predicate : newPredicatesList)
                            {
                                agent->OnNewPredicate(predicate);
                            }
                        }
                        return true;
                    }
                    return false;
                });*/
			
        }
    }
}