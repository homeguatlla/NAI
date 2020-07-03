#pragma once
#include "source/goap/BaseAction.h"
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
		class GoToGoal;
		class IAgent;
		
		class FindPathToAction : public BaseAction
		{
		public:
			FindPathToAction(
				std::shared_ptr<GoToGoal> goal,
				const std::vector<std::shared_ptr<IPredicate>>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions,
				std::shared_ptr<IAgent> agent,
				std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner);
			virtual ~FindPathToAction() = default;

			void Process(float elapsedTime) override;

		private:
			std::string GetPlaceToGo() const;

			std::shared_ptr<GoToGoal> mGoal;
			std::shared_ptr<IAgent> mAgent;
			std::shared_ptr<Navigation::INavigationPlanner> mNavigationPlanner;
		};
	}
}
