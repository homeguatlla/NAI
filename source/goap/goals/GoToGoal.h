#pragma once
#include "goap/BaseGoal.h"
#include "goap/actions/FollowPathAction.h"
#include "goap/actions/FindPathToAction.h"
#include <vector>
#include <memory>
#include <string>

#include "IGoToGoal.h"


namespace NAI
{
	namespace Navigation
	{
		class INavigationPlanner;
		class INavigationPath;
	}

	namespace Goap
	{
		class IAgent;

		class GoToGoal : public BaseGoal, public IGoToGoal
		{
		public:
			GoToGoal(const std::shared_ptr<Navigation::INavigationPlanner>& navigationPlanner, float precision = 0.01f);
			~GoToGoal() override = default;
			void OnNavigationPath(const std::string& placeName, const std::shared_ptr<Navigation::INavigationPath>& path) override;
			unsigned int GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates, std::vector<std::shared_ptr<IPredicate>>& accomplishedPredicates) const override;
			glm::vec3 GetDestination(const std::shared_ptr<IPredicate> predicate) const override;
		
		protected:
			void DoCreate(const std::shared_ptr<IAgent>& agent) override;
			void DoAccomplished(std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			void DoReset(std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			void DoCancel(std::vector<std::shared_ptr<IPredicate>>& predicates) override;
		
		private:
			std::shared_ptr<FollowPathAction> CreateFollowPathAction(const std::weak_ptr<IAgent>& agent, const std::string& placeName, const std::shared_ptr<Navigation::INavigationPath>& navigationPath) const;
			std::shared_ptr<FindPathToAction> CreateFindPathToAction(const std::weak_ptr<IAgent>& agent, const std::shared_ptr<Navigation::INavigationPlanner>& navigationPlanner);
			void RemovePredicateGoTo(std::vector<std::shared_ptr<IPredicate>>& predicates) const;
			void UpdatePlaceIamPredicate(std::vector<std::shared_ptr<IPredicate>>& predicates) const;			
		
		private:
			std::weak_ptr<IAgent> mAgent;
			std::shared_ptr<Navigation::INavigationPlanner> mNavigationPlanner;
			std::string mPlaceName;
			float mPrecision;
		};
	}
}
