#include "pch.h"
#include "CognitiveSystem.h"

#include <goap/agent/IAgent.h>

#include "goap/IPredicate.h"

namespace NAI
{
    namespace Goap
    {
        void CognitiveSystem::Update(
            float elapsedTime,
            ShortTermMemory<IStimulus>& memory,
            std::shared_ptr<IAgent> agent)
        {
            const auto newPredicatesList = agent->TransformStimulusIntoPredicates(memory);
            if(!newPredicatesList.empty())
            {
                //TODO we can evaluate each predicate to really see if we must add it or not into the
                //predicates list of the agent.
               
                const auto predicatesList = agent->GetPredicates();

                for(auto&& predicate : newPredicatesList)
                {
                    auto found = std::find_if(predicatesList.begin(), predicatesList.end(),
                        [predicate](const std::shared_ptr<IPredicate> p)
                        {
                            return predicate->GetID() == p->GetID();
                        }) != predicatesList.end();
                    if(!found)
                    {
                        agent->OnNewPredicate(predicate);
                    }
                    else
                    {
                        agent->OnUpdatePredicate(predicate);
                    }
                }
            }
        }
    }
}
