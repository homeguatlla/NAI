#include "pch.h"
#include "AgentBuilder.h"

namespace NAI
{
    namespace  Goap
    {
        AgentBuilder& AgentBuilder::WithGoal(std::shared_ptr<IGoal> goal)
        {
            mGoals.push_back(goal);

            return *this;
        }

        AgentBuilder& AgentBuilder::WithPredicate(std::shared_ptr<IPredicate> predicate)
        {
            mPredicates.push_back(predicate);

            return *this;
        }

        AgentBuilder& AgentBuilder::WithGoapPlanner(std::shared_ptr<IGoapPlanner> planner)
        {
            mGoapPlanner = planner;
            
            return *this;
        }

        AgentBuilder& AgentBuilder::WithSensoryThreshold(const std::string& stimulusClassName,
            std::shared_ptr<IThreshold> threshold)
        {
            mSensoryThresholds[stimulusClassName] = threshold;
            return *this;
        }

        AgentBuilder& AgentBuilder::WithPerceptionSystem(std::shared_ptr<SensorySystem<IStimulus>> sensorySystem)
        {
            mSensorySystem = sensorySystem;
            return *this;
        }
    }
}
