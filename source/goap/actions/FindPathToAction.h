#pragma once
#include "goap/BaseAction.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <string>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPlanner;
	}

	namespace Goap
	{
		class IGoToGoal;
		class IAgent;
		
		class FindPathToAction : public BaseAction
		{
		public:
			FindPathToAction(
				const std::shared_ptr<IGoToGoal>& goal,
				const std::vector<std::string>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions,
				const std::weak_ptr<IAgent>& agent,
				const std::shared_ptr<Navigation::INavigationPlanner>& navigationPlanner);
			~FindPathToAction() override = default;

			void Process(float elapsedTime) override;

		private:
			std::string GetPlaceToGo() const;
			
			std::weak_ptr<IGoToGoal> mGoal;
			std::weak_ptr<IAgent> mAgent;
			std::shared_ptr<Navigation::INavigationPlanner> mNavigationPlanner;
			bool mWaitingForPath;
		};
	}
}
