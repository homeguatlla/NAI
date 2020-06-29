#include "pch.h"
#include "GoToGoal.h"
#include "source/goap/actions/FindPathToAction.h"
#include "source/goap/actions/FollowPathAction.h"
#include "source/goap/predicates/GoToPredicate.h"
#include "source/goap/predicates/GoapPredicates.h"
#include <vector>

namespace NAI
{
	namespace Goap
	{
		GoToGoal::GoToGoal()
		{
			mActions.push_back(CreateFindPathToAction());
		}
		
		std::shared_ptr<IAction> GoToGoal::CreateFindPathToAction()
		{
			std::vector<std::shared_ptr<IPredicate>> preconditions, postconditions;
			preconditions.push_back(PREDICATE_GO_TO);
			postconditions.push_back(PREDICATE_GOT_PATH);

			auto findPathTo = std::make_shared<FindPathToAction>(preconditions, postconditions);

			return findPathTo;
		}

		std::shared_ptr<IAction>  GoToGoal::CreateFollowPathAction()
		{
			std::vector<std::shared_ptr<IPredicate>> preconditions, postconditions;
			preconditions.push_back(PREDICATE_GOT_PATH);
			postconditions.push_back(PREDICATE_AT_PLACE);

			auto findPathTo = std::make_shared<FindPathToAction>(preconditions, postconditions);

			return findPathTo;
		}
	}
}
