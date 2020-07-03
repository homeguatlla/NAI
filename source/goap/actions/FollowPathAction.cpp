#include "pch.h"
#include "FollowPathAction.h"

namespace NAI
{
	namespace Goap
	{
		FollowPathAction::FollowPathAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			std::shared_ptr<Navigation::INavigationPath> path ) :
			BaseAction(preConditions, postConditions, 0),
			mPath{ path }
		{
		}
	}
}
