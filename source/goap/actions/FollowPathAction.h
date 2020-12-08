#pragma once
#include "goap/BaseAction.h"
#include <memory>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPath;
	}
	namespace Goap
	{
		class IAgent;

		class FollowPathAction : public BaseAction
		{
		public:
			FollowPathAction(
				const std::vector<std::shared_ptr<IPredicate>>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions,
				std::weak_ptr<IAgent> agent,
				std::shared_ptr<Navigation::INavigationPath> path);
			virtual ~FollowPathAction() = default;
			void Process(float elapsedTime) override;

		private:
			std::shared_ptr<Navigation::INavigationPath> mPath;
			std::weak_ptr<IAgent> mAgent;
			unsigned int mCurrentPointIndex;
		};
	}
}
