#pragma once
#include "goap/IGoal.h"
#include "goap/IGoapPlanner.h"
#include "goap/IPredicate.h"
#include "goap/sensory/IThreshold.h"

#include <map>
#include <memory>
#include <vector>
#include <type_traits>

#include "IAgent.h"
#include "goap/sensory/PerceptionSystem.h"
#include "goap/sensory/SensorySystem.h"


namespace NAI {
    namespace Goap {
        class IAgent;

        class AgentBuilder
        {
        public:
            AgentBuilder() = default;
            ~AgentBuilder() = default;

            AgentBuilder& WithGoal(std::shared_ptr<IGoal> goal);
            AgentBuilder& WithPredicate(std::shared_ptr<IPredicate> predicate);
            AgentBuilder& WithGoapPlanner(std::shared_ptr<IGoapPlanner> planner);
            AgentBuilder& WithSensoryThreshold(const std::string& stimulusClassName, std::shared_ptr<IThreshold> threshold);
            AgentBuilder& WithPerceptionSystem(std::shared_ptr<SensorySystem<IStimulus>> sensorySystem);
            
            template<class TAgent>
            std::shared_ptr<IAgent> Build() const
            {
                static_assert(std::is_base_of<IAgent, TAgent>::value, "class Type must inherit from IAgent");

                std::shared_ptr<IAgent> agent;
                if(mSensorySystem != nullptr)
                {
                    agent = std::make_shared<TAgent>(
                        mGoapPlanner,
                        mGoals,
                        mPredicates,
                        std::make_shared<PerceptionSystem>(mSensorySystem));
                }
                else
                {
                    agent = std::make_shared<TAgent>(
                        mGoapPlanner,
                        mGoals,
                        mPredicates);
                }
                
                for(auto&& threshold : mSensoryThresholds)
                {
                    agent->AddSensoryThreshold(threshold.first, threshold.second);
                }
                return agent;
            }

        protected:
            std::vector<std::shared_ptr<IPredicate>> mPredicates;
            std::vector<std::shared_ptr<IGoal>> mGoals;
            std::shared_ptr<IGoapPlanner> mGoapPlanner;
            std::map<std::string, std::shared_ptr<IThreshold>> mSensoryThresholds;
            std::shared_ptr<SensorySystem<IStimulus>> mSensorySystem;
        };
    }
}
