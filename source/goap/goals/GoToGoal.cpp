#include "pch.h"
#include "GoToGoal.h"
#include "source/goap/actions/FindPathToAction.h"
#include "source/goap/actions/FollowPathAction.h"
#include "source/goap/predicates/GoToPredicate.h"
#include "source/goap/predicates/GoapPredicates.h"
#include "source/goap/predicates/PlaceIamPredicate.h"
#include "source/goap/agent/IAgent.h"
#include "source/goap/GoapUtils.h"
#include "source/navigation/INavigationPath.h"
#include "source/navigation/INavigationPlanner.h"


#include <vector>

namespace NAI
{
	namespace Goap
	{
		GoToGoal::GoToGoal(std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner) :
		mNavigationPlanner { navigationPlanner }
		{
		}

		void GoToGoal::DoCreate(std::shared_ptr<IAgent> agent)
		{
			mAgent = agent;
			Reset();
		}

		void GoToGoal::DoReset()
		{
			mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
		}

		const unsigned int GoToGoal::GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
		{
			if(!inputPredicates.empty())
			{ 
				if(auto agent = mAgent.lock())
				{
					auto goToPredicate = std::static_pointer_cast<GoToPredicate>(inputPredicates[0]);
					auto destination = mNavigationPlanner->GetLocationGivenAName(goToPredicate->GetPlaceName());

					return mNavigationPlanner->GetAproxCost(agent->GetPosition(), destination);
				}
			}

			return std::numeric_limits<unsigned int>::max();
		}

		void GoToGoal::DoAccomplished(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			RemovePredicateGoTo(predicates);
			Utils::RemovePredicateWith(predicates, "GotPath");

			std::shared_ptr<IPredicate> predicate;
			if (Utils::FindPredicateWith(predicates, "PlaceIam", predicate))
			{
				auto placeIamPredicate = std::static_pointer_cast<PlaceIamPredicate>(predicate);
				if (placeIamPredicate->GetPlaceName() != mPlaceName)
				{
					Utils::RemovePredicateWith(predicates, "PlaceIam");
				}
			}
		}

		void GoToGoal::RemovePredicateGoTo(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			std::shared_ptr<IPredicate> predicate;
			if (Utils::FindPredicateWith(predicates, "PlaceIam", predicate))
			{
				auto placeIamPredicate = std::static_pointer_cast<PlaceIamPredicate>(predicate);
				auto placeName = placeIamPredicate->GetPlaceName();

				auto it = std::find_if(predicates.begin(), predicates.end(),
					[&placeName](const std::shared_ptr<IPredicate> predicate)
					{
						if (predicate->GetText() == "GoTo")
						{
							auto goToPredicate = std::static_pointer_cast<GoToPredicate>(predicate);
							return goToPredicate->GetPlaceName() == placeName;
						}
						else
						{
							return false;
						}
					});
				if (it != predicates.end())
				{
					predicates.erase(it);
				}
			}
		}

		void GoToGoal::OnNavigationPath(const std::string& placeName, std::shared_ptr<Navigation::INavigationPath> path)
		{
			if(!path->Empty())
			{
				mPlaceName = placeName;
				mActions.push_back(CreateFollowPathAction(mAgent, placeName, path));
			}
			else
			{
				//TODO Cancel();
			}
		}
		
		std::shared_ptr<IAction> GoToGoal::CreateFindPathToAction(std::weak_ptr<IAgent> agent, std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner)
		{
			std::vector<std::shared_ptr<IPredicate>> preconditions, postconditions;
			preconditions.push_back(Predicates::PREDICATE_GO_TO);
			postconditions.push_back(Predicates::PREDICATE_GOT_PATH);

			auto goal = std::static_pointer_cast<GoToGoal>(shared_from_this());
			auto findPathTo = std::make_shared<FindPathToAction>(goal, preconditions, postconditions, agent, navigationPlanner);

			return findPathTo;
		}

		std::shared_ptr<IAction> GoToGoal::CreateFollowPathAction(std::weak_ptr<IAgent> agent, const std::string& placeName, std::shared_ptr<Navigation::INavigationPath> navigationPath)
		{
			std::vector<std::shared_ptr<IPredicate>> preconditions, postconditions;
			preconditions.push_back(Predicates::PREDICATE_GOT_PATH);
			postconditions.push_back(std::make_shared<PlaceIamPredicate>("PlaceIam", placeName));

			auto followPathTo = std::make_shared<FollowPathAction>(preconditions, postconditions, agent, navigationPath);

			return followPathTo;
		}
	}
}
