#pragma once
#include "IAgent.h"
#include "AgentContext.h"
#include "goap/GoapTypes.h"
#include "utils/fsm/StatesMachine.h"
#include "goap/agent/fsm/states/Planning.h"
#include "goap/PredicatesHandler.h"
#include <vector>
#include <memory>


namespace NAI
{
	namespace Goap
	{
		class IGoal;

		class BaseAgent : public IAgent, public std::enable_shared_from_this<BaseAgent>
		{
		public:
			BaseAgent(	std::shared_ptr<IGoapPlanner> goapPlanner, 
						const std::vector<std::shared_ptr<IGoal>>& goals, 
						const std::vector<std::shared_ptr<IPredicate>>& predicates);
			virtual ~BaseAgent() = default;

			AgentState GetCurrentState() const override;
			void StartUp() override;
			void Update(float elapsedTime) override;
			bool HasPredicate(int predicateID) const override;
			std::string WhereIam() const override;
			void OnNewPredicate(std::shared_ptr<IPredicate> predicate) override;
			const std::vector<std::shared_ptr<IGoal>>& GetGoals() const override { return mGoals; }
			const std::vector<std::shared_ptr<IPredicate>>& GetPredicates() const override { return mPredicatesHandler.GetPredicatesList(); }
			bool IsStimulusAccepted(std::shared_ptr<IStimulus> stimulus) const override;
			const std::vector<std::shared_ptr<IPredicate>> TransformStimulusIntoPredicates(std::shared_ptr<IStimulus> stimulus) const override;
			std::map<std::string, std::shared_ptr<IThreshold>> GetSensoryThresholds() const override { return mThresholds; }
			void AddSensoryThreshold(const std::string& stimulusClassName, std::shared_ptr<IThreshold> threshold) override;
		
		private:
			void CreateStatesMachine();
			void NotifyPredicatesListChangedToProcessState();

		private:
			std::unique_ptr<core::utils::FSM::StatesMachine<AgentState, AgentContext>> mStatesMachine;
			std::shared_ptr<AgentContext> mAgentContext;
			std::shared_ptr<IGoapPlanner> mGoapPlanner;
			PredicatesHandler mPredicatesHandler;
			std::vector<std::shared_ptr<IGoal>> mGoals;
			std::map<std::string, std::shared_ptr<IThreshold>> mThresholds;
		};
	}
}

