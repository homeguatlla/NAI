#pragma once
#include "goap/planners/DirectGoapPlanner.h"
#include "goap/PredicatesHandler.h"

namespace NAI
{
	namespace Goap
	{
		class AgentContext
		{
		public:
			AgentContext(	std::shared_ptr<IGoapPlanner> planner, 
							const PredicatesHandler& predicatesHandler,
							std::vector<std::shared_ptr<IGoal>>& goals);

			//Planner
			std::shared_ptr<IGoapPlanner> GetGoapPlanner() const { return mGoapPlanner; }

			//Current Plan
			void SetPlan(std::shared_ptr<IGoal> plan);
			std::shared_ptr<IGoal> GetPlan() const { return mCurrentPlan; }
			bool HasPlan() const { return mCurrentPlan != nullptr; }

			//Predicates
			PredicatesHandler GetPredicatesHandler() const { return mPredicatesHandler; }
			void  SetPredicatesHandler(const PredicatesHandler& predicatesHandler) { mPredicatesHandler = predicatesHandler; }

			//Goals
			std::vector<std::shared_ptr<IGoal>> GetGoals() const { return mGoals; }

			virtual ~AgentContext() = default;

			private:
				std::shared_ptr<IGoapPlanner> mGoapPlanner;
				std::shared_ptr<IGoal> mCurrentPlan;
				PredicatesHandler mPredicatesHandler;
				std::vector<std::shared_ptr<IGoal>> mGoals;
		};
	}
}

