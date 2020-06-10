#include "pch.h"
#include "Action.h"

namespace NAI
{
	Action::Action(std::vector<std::shared_ptr<Predicate>>& predicates) : mPreconditions{ predicates }
	{
	}
}
