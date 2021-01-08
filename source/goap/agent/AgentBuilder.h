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
            
            template<class TAgent>
            std::shared_ptr<IAgent> Build() const
            {
                static_assert(std::is_base_of<IAgent, TAgent>::value, "class Type must inherit from IAgent");
                
                std::shared_ptr<IAgent> agent = std::make_shared<TAgent>(mGoapPlanner, mGoals, mPredicates);
                for(auto&& threshold : mSensoryThresholds)
                {
                    agent->AddSensoryThreshold(threshold.first, threshold.second);
                }
                return agent;
            }

        private:
            std::vector<std::shared_ptr<IPredicate>> mPredicates;
            std::vector<std::shared_ptr<IGoal>> mGoals;
            std::shared_ptr<IGoapPlanner> mGoapPlanner;
            std::map<std::string, std::shared_ptr<IThreshold>> mSensoryThresholds;
        };
    }
}
