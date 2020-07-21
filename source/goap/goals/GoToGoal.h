#pragma once
#include "source/goap/BaseGoal.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <string>

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

		class GoToGoal : public BaseGoal
		{
		public:
			GoToGoal(std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner);
			void Create(std::shared_ptr<IAgent> agent);
			virtual ~GoToGoal() = default;
			void OnNavigationPath(const std::string& placeName, std::shared_ptr<Navigation::INavigationPath> path);
			const unsigned int GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const override;

		protected:
			void DoAccomplished(std::vector<std::shared_ptr<IPredicate>>& predicates) override;

		private:
			std::shared_ptr<IAction> CreateFollowPathAction(std::weak_ptr<IAgent> agent, const std::string& placeName, std::shared_ptr<Navigation::INavigationPath> navigationPath);
			std::shared_ptr<IAction> CreateFindPathToAction(std::weak_ptr<IAgent> agent, std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner);

		private:
			std::weak_ptr<IAgent> mAgent;
			std::shared_ptr<Navigation::INavigationPlanner> mNavigationPlanner;
		};
	}
}
