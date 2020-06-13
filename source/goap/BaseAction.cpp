#include "pch.h"
#include "BaseAction.h"

namespace NAI
{
	BaseAction::BaseAction(
		const std::vector<std::shared_ptr<IPredicate>>& predicates,
		const std::vector<std::shared_ptr<IPredicate>>& postconditions,
		unsigned int cost) : 
		mPreconditions{ predicates },
		mPostconditions { postconditions },
		mCost { cost }
	{
	}
}
