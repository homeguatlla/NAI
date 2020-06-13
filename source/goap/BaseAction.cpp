#include "pch.h"
#include "BaseAction.h"

namespace NAI
{
	namespace Goap
	{
		BaseAction::BaseAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			unsigned int cost) :
			mPreConditions{ preConditions },
			mPostConditions{ postConditions },
			mCost{ cost }
		{
		}

		void BaseAction::Process(float elapsedTime)
		{

		}
	}
}
