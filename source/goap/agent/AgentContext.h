#pragma once
#include "source/goap/planners/DirectGoapPlanner.h"

namespace NAI
{
	namespace Goap
	{
		class AgentContext
		{
		public:
			AgentContext(	std::shared_ptr<IGoapPlanner> planner, 
							std::vector<std::shared_ptr<IPredicate>>& predicates,
							std::vector<std::shared_ptr<IGoal>>& goals);

			//Planner
			std::shared_ptr<IGoapPlanner> GetGoapPlanner() const { return mGoapPlanner; }

			//Current Plan
			void SetPlan(std::shared_ptr<IGoal> plan);
			std::shared_ptr<IGoal> GetPlan() const { return mCurrentPlan; }
			bool HasPlan() const { return mCurrentPlan != nullptr; }

			//Predicates
			std::vector<std::shared_ptr<IPredicate>> GetPredicates() { return mPredicates; }
			void  SetPredicates(std::vector<std::shared_ptr<IPredicate>> predicates) { mPredicates = predicates; }

			//Goals
			std::vector<std::shared_ptr<IGoal>> GetGoals() const { return mGoals; }

			virtual ~AgentContext() = default;

			private:
				std::shared_ptr<IGoapPlanner> mGoapPlanner;
				std::shared_ptr<IGoal> mCurrentPlan;
				std::vector<std::shared_ptr<IPredicate>> mPredicates;
				std::vector<std::shared_ptr<IGoal>> mGoals;
		};
	}
}

