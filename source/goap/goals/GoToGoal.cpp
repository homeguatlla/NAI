#include "pch.h"
#include "GoToGoal.h"
#include "source/goap/actions/FindPathToAction.h"
#include "source/goap/actions/FollowPathAction.h"
#include "source/goap/predicates/GoToPredicate.h"
#include "source/goap/predicates/GoapPredicates.h"
#include "source/navigation/INavigationPath.h"
#include <vector>

namespace NAI
{
	namespace Goap
	{
		GoToGoal::GoToGoal(std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner) :
		mNavigationPlanner { navigationPlanner }
		{
		}

		void GoToGoal::Create(std::shared_ptr<IAgent> agent)
		{
			mAgent = agent;
			mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
		}

		void GoToGoal::OnNavigationPath(std::shared_ptr<Navigation::INavigationPath> path)
		{
			mNavigationPath = path;
			if(!mNavigationPath->Empty())
			{
				//CreateFollowPathAction
			}
		}
		
		std::shared_ptr<IAction> GoToGoal::CreateFindPathToAction(std::shared_ptr<IAgent> agent, std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner)
		{
			std::vector<std::shared_ptr<IPredicate>> preconditions, postconditions;
			preconditions.push_back(PREDICATE_GO_TO);
			postconditions.push_back(PREDICATE_GOT_PATH);

			auto goal = std::dynamic_pointer_cast<GoToGoal>(shared_from_this());
			auto findPathTo = std::make_shared<FindPathToAction>(goal, preconditions, postconditions, agent, navigationPlanner);

			return findPathTo;
		}

		std::shared_ptr<IAction>  GoToGoal::CreateFollowPathAction()
		{
			std::vector<std::shared_ptr<IPredicate>> preconditions, postconditions;
			preconditions.push_back(PREDICATE_GOT_PATH);
			postconditions.push_back(PREDICATE_AT_PLACE);

			//auto followPathTo = std::make_shared<FollowPathAction>(preconditions, postconditions);

			return nullptr;
		}
	}
}
