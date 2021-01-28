#include "pch.h"
#include "GoToGoal.h"
#include "goap/actions/FindPathToAction.h"
#include "goap/actions/FollowPathAction.h"
#include "goap/predicates/GoToPredicate.h"
#include "goap/predicates/GoapPredicates.h"
#include "goap/predicates/PlaceIamPredicate.h"
#include "goap/agent/IAgent.h"
#include "goap/GoapUtils.h"
#include "navigation/INavigationPath.h"
#include "navigation/INavigationPlanner.h"


#include <vector>

namespace NAI
{
	namespace Goap
	{
		GoToGoal::GoToGoal(const std::shared_ptr<Navigation::INavigationPlanner>& navigationPlanner, float precision) :
		mNavigationPlanner { navigationPlanner },
		mPrecision { precision }
		{
		}

		void GoToGoal::DoCreate(const std::shared_ptr<IAgent>& agent)
		{
			mAgent = agent;
			Reset();
		}

		void GoToGoal::DoReset()
		{
			mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
		}

		unsigned int GoToGoal::GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
		{
			if(!inputPredicates.empty())
			{ 
				if(const auto agent = mAgent.lock())
				{
					const auto goToPredicate = std::static_pointer_cast<GoToPredicate>(inputPredicates[0]);
					const auto destination = mNavigationPlanner->GetLocationGivenAName(goToPredicate->GetPlaceName());

					return mNavigationPlanner->GetAproxCost(agent->GetPosition(), destination);
				}
			}

			return std::numeric_limits<unsigned int>::max();
		}

		void GoToGoal::DoAccomplished(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			UpdatePlaceIamPredicate(predicates);
			RemovePredicateGoTo(predicates);
			Utils::RemovePredicateWith(predicates, "GotPath");
		}

		void GoToGoal::UpdatePlaceIamPredicate(std::vector<std::shared_ptr<IPredicate>>& predicates) const
		{
			std::shared_ptr<IPredicate> predicate;
			if (Utils::FindPredicateWith(predicates, "PlaceIam", predicate))
			{
				const auto placeIamPredicate = std::static_pointer_cast<PlaceIamPredicate>(predicate);
				if (placeIamPredicate->GetPlaceName() != mPlaceName)
				{
					Utils::RemovePredicateWith(predicates, "PlaceIam");
				}
			}
		}

		void GoToGoal::RemovePredicateGoTo(std::vector<std::shared_ptr<IPredicate>>& predicates) const
		{
			std::shared_ptr<IPredicate> predicateFound;
			if (Utils::FindPredicateWith(predicates, "PlaceIam", predicateFound))
			{
				const auto placeIamPredicate = std::static_pointer_cast<PlaceIamPredicate>(predicateFound);
				auto placeName = placeIamPredicate->GetPlaceName();

				const auto it = std::find_if(predicates.begin(), predicates.end(),
					[&placeName](const std::shared_ptr<IPredicate>& predicate)
					{
						if (predicate->GetText() == "GoTo")
						{
							const auto goToPredicate = std::static_pointer_cast<GoToPredicate>(predicate);
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

		void GoToGoal::OnNavigationPath(const std::string& placeName, const std::shared_ptr<Navigation::INavigationPath>& path)
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
		
		std::shared_ptr<FindPathToAction> GoToGoal::CreateFindPathToAction(const std::weak_ptr<IAgent>& agent, const std::shared_ptr<Navigation::INavigationPlanner>& navigationPlanner)
		{
			std::vector<std::string> preConditions;
			std::vector<std::shared_ptr<IPredicate>> postConditions;
			preConditions.push_back(Predicates::PREDICATE_GO_TO->GetText());
			postConditions.push_back(Predicates::PREDICATE_GOT_PATH);

			const auto goal = std::static_pointer_cast<GoToGoal>(shared_from_this());
			auto findPathTo = std::make_shared<FindPathToAction>(goal, preConditions, postConditions, agent, navigationPlanner);

			return findPathTo;
		}

		std::shared_ptr<FollowPathAction> GoToGoal::CreateFollowPathAction(const std::weak_ptr<IAgent>& agent, const std::string& placeName, const std::shared_ptr<Navigation::INavigationPath>& navigationPath) const
		{
			std::vector<std::string> preConditions;
			std::vector<std::shared_ptr<IPredicate>> postConditions;
			preConditions.push_back(Predicates::PREDICATE_GOT_PATH->GetText());
			postConditions.push_back(std::make_shared<PlaceIamPredicate>("PlaceIam", placeName));

			auto followPathTo = std::make_shared<FollowPathAction>(preConditions, postConditions, agent, navigationPath, mPrecision);

			return followPathTo;
		}
	}
}
