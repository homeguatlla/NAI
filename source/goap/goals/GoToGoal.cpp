#include "pch.h"
#include "GoToGoal.h"
#include "goap/actions/FindPathToAction.h"
#include "goap/actions/FollowPathAction.h"
#include "goap/predicates/GoToPredicate.h"
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
			mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
		}

		void GoToGoal::DoReset(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			Utils::RemovePredicateWith(predicates, PREDICATE_GOT_PATH_NAME);
			mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
		}

		void GoToGoal::DoCancel(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			Utils::RemovePredicateWith(predicates, PREDICATE_GOT_PATH_NAME);
		}

		unsigned int GoToGoal::GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates, std::vector<std::shared_ptr<IPredicate>>& accomplishedPredicates) const
		{
			if(!accomplishedPredicates.empty())
			{ 
				if(const auto agent = mAgent.lock())
				{
					const auto goToPredicate = std::static_pointer_cast<GoToPredicate>(accomplishedPredicates[0]);
					const glm::vec3 destination = GetDestination(goToPredicate);
					
					return mNavigationPlanner->GetAproxCost(agent->GetPosition(), destination);
				}
			}

			return std::numeric_limits<unsigned int>::max();
		}

		void GoToGoal::DoAccomplished(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			predicates.push_back(std::make_shared<PlaceIamPredicate>(PLACE_IAM_PREDICATE_ID, PLACE_IAM_PREDICATE_NAME, mPlaceName));
			UpdatePlaceIamPredicate(predicates);
			RemovePredicateGoTo(predicates);
			Utils::RemovePredicateWith(predicates, PREDICATE_GOT_PATH_NAME);
			
		}

		void GoToGoal::UpdatePlaceIamPredicate(std::vector<std::shared_ptr<IPredicate>>& predicates) const
		{
			std::shared_ptr<IPredicate> predicate;
			if (Utils::FindPredicateWith(predicates, PLACE_IAM_PREDICATE_NAME, predicate))
			{
				const auto placeIamPredicate = std::static_pointer_cast<PlaceIamPredicate>(predicate);
				if (placeIamPredicate->GetPlaceName() != mPlaceName)
				{
					Utils::RemovePredicateWith(predicates, PLACE_IAM_PREDICATE_NAME);
				}
			}
		}

		void GoToGoal::RemovePredicateGoTo(std::vector<std::shared_ptr<IPredicate>>& predicates) const
		{
			std::shared_ptr<IPredicate> predicateFound;
			if (Utils::FindPredicateWith(predicates, PLACE_IAM_PREDICATE_NAME, predicateFound))
			{
				const auto placeIamPredicate = std::static_pointer_cast<PlaceIamPredicate>(predicateFound);
				auto placeName = placeIamPredicate->GetPlaceName();

				const auto it = std::find_if(predicates.begin(), predicates.end(),
					[&placeName](const std::shared_ptr<IPredicate>& predicate)
					{
						if (predicate->GetText() == PREDICATE_GO_TO_NAME)
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
			preConditions.push_back(PREDICATE_GO_TO_NAME);
			postConditions.push_back(std::make_shared<BasePredicate>(PREDICATE_GOT_PATH_ID, PREDICATE_GOT_PATH_NAME));

			const auto goal = std::static_pointer_cast<GoToGoal>(shared_from_this());
			auto findPathTo = std::make_shared<FindPathToAction>(goal, preConditions, postConditions, agent, navigationPlanner);

			return findPathTo;
		}

		std::shared_ptr<FollowPathAction> GoToGoal::CreateFollowPathAction(const std::weak_ptr<IAgent>& agent, const std::string& placeName, const std::shared_ptr<Navigation::INavigationPath>& navigationPath) const
		{
			std::vector<std::string> preConditions;
			std::vector<std::shared_ptr<IPredicate>> postConditions;
			preConditions.push_back(PREDICATE_GOT_PATH_NAME);
			
			auto followPathTo = std::make_shared<FollowPathAction>(preConditions, postConditions, agent, navigationPath, mPrecision);

			return followPathTo;
		}

		glm::vec3 GoToGoal::GetDestination(const std::shared_ptr<IPredicate> predicate) const
		{
			const auto goToPredicate = std::static_pointer_cast<GoToPredicate>(predicate);
			glm::vec3 destination(0.0f);
			const auto hasDestination = mNavigationPlanner->FillWithLocationGivenAName(goToPredicate->GetPlaceName(), destination);

			if(!hasDestination)
			{
				destination = goToPredicate->GetLocation();
			}

			return destination;
		}
	}
}
