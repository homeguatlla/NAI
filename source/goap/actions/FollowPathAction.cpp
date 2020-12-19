#include "pch.h"
#include "FollowPathAction.h"
#include "goap/agent/IAgent.h"
#include "navigation/INavigationPath.h"

namespace NAI
{
	namespace Goap
	{
		FollowPathAction::FollowPathAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			std::weak_ptr<IAgent> agent,
			std::shared_ptr<Navigation::INavigationPath> path,
			float precision) :
			BaseAction(preConditions, postConditions, 0),
			mPath{ path },
			mAgent { agent },
			mCurrentPointIndex {1},
			mPrecision { precision }
		{
			mHasAccomplished = false;
		}

		void FollowPathAction::Process(float elapsedTime)
		{
			if (auto agent = mAgent.lock())
			{
				const auto hasReachedPoint = mPath->HasReachedPoint(mCurrentPointIndex, agent->GetPosition(), mPrecision);
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
