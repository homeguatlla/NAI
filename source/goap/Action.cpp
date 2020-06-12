#include "pch.h"
#include "Action.h"

namespace NAI
{
	Action::Action(
		const std::vector<std::shared_ptr<Predicate>>& predicates,
		const std::vector<std::shared_ptr<Predicate>>& postconditions,
		unsigned int cost) : 
		mPreconditions{ predicates },
		mPostconditions { postconditions },
		mCost { cost }
	{
	}
}
