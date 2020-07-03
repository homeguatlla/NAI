#pragma once
#include "IAgent.h"
#include "AgentContext.h"
#include "source/goap/GoapTypes.h"
#include "source/utils/fsm/StatesMachine.h"
#include "source/goap/agent/fsm/states/Planning.h"
#include "source/goap/agent/fsm/states/Processing.h"
#include "source/goap/agent/fsm/transitions/EnterPlanning.h"
#include "source/goap/agent/fsm/transitions/EnterProcessing.h"
#include <vector>
#include <memory>


namespace NAI
{
	namespace Goap
	{
		class IGoal;

		class BaseAgent : public IAgent
		{
		public:
			BaseAgent(	std::shared_ptr<IGoapPlanner> goapPlanner, 
						std::vector<std::shared_ptr<IGoal>>& goals, 
						std::vector<std::shared_ptr<IPredicate>>& predicates,
						const glm::vec3& position = glm::vec3(0.0f));
			virtual ~BaseAgent() = default;

			AgentState GetCurrentState() const override;
			void Update(float elapsedTime) override;
			bool HasPredicate(int predicateID) const override;
			void OnNewPredicate(std::shared_ptr<IPredicate> predicate) override;
			std::vector<std::shared_ptr<IGoal>> GetGoals() const override { return mGoals; }
			glm::vec3 GetPosition() const override { return mPosition; }
		private:
			void CreateStatesMachine();
			void NotifyPredicatesListChangedToProcessState();

		private:
			std::unique_ptr<core::utils::FSM::StatesMachine<AgentState, AgentContext>> mStatesMachine;
			std::shared_ptr<AgentContext> mAgentContext;
			std::shared_ptr<IGoapPlanner> mGoapPlanner;
			std::vector<std::shared_ptr<IPredicate>> mPredicates;
			std::vector<std::shared_ptr<IGoal>> mGoals;
			glm::vec3 mPosition;
		};
	}
}

