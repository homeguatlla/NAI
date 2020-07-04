#pragma once
#include "source/goap/BaseGoal.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

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
			void OnNavigationPath(std::shared_ptr<Navigation::INavigationPath> path);
			std::shared_ptr<Navigation::INavigationPath> GetNavigationPath() { return mNavigationPath; }

		private:
			std::shared_ptr<IAction> CreateFollowPathAction(std::shared_ptr<Navigation::INavigationPath> navigationPath);
			std::shared_ptr<IAction> CreateFindPathToAction(std::weak_ptr<IAgent> agent, std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner);
		
		private:
			std::weak_ptr<IAgent> mAgent;
			std::shared_ptr<Navigation::INavigationPlanner> mNavigationPlanner;
			std::shared_ptr<Navigation::INavigationPath> mNavigationPath;
		};
	}
}
