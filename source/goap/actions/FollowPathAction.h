#pragma once
#include "source/goap/BaseAction.h"
#include <memory>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPath;
	}
	namespace Goap
	{
		class FollowPathAction : public BaseAction
		{
		public:
			FollowPathAction(
				const std::vector<std::shared_ptr<IPredicate>>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions,
				std::shared_ptr<Navigation::INavigationPath> path);
			virtual ~FollowPathAction() = default;

		private:
			std::shared_ptr<Navigation::INavigationPath> mPath;
		};
	}
}
