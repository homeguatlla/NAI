#include "pch.h"
#include "FollowPathAction.h"
#include "source/goap/agent/IAgent.h"
#include "source/navigation/INavigationPath.h"

namespace NAI
{
	namespace Goap
	{
		FollowPathAction::FollowPathAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			std::weak_ptr<IAgent> agent,
			std::shared_ptr<Navigation::INavigationPath> path ) :
			BaseAction(preConditions, postConditions, 0),
			mPath{ path },
			mAgent { agent },
			mCurrentPointIndex {1}
		{
			mHasAccomplished = false;
		}

		void FollowPathAction::Process(float elapsedTime)
		{
			if (auto agent = mAgent.lock())
			{
				const auto hasReachedPoint = mPath->HasReachedPoint(mCurrentPointIndex, agent->GetPosition(), MOVEMENT_PRECISION);
				if (hasReachedPoint)
				{
					if(mPath->IsEndOfPath(mCurrentPointIndex))
					{
						mHasAccomplished = true;
					}
					else
					{
						mCurrentPointIndex++;
					}
				}
				else
				{
					agent->MoveTo(elapsedTime, mPath->GetPoint(mCurrentPointIndex));
				}
			}
		}
	}
}
