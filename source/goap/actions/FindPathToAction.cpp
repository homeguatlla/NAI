#include "pch.h"
#include "FindPathToAction.h"
#include "source/goap/agent/IAgent.h"
#include "source/goap/goals/GoToGoal.h"
#include "source/goap/IPredicate.h"
#include "source/goap/predicates/GoToPredicate.h"
#include "source/navigation/INavigationPlanner.h"


namespace NAI
{
	namespace Goap
	{
		FindPathToAction::FindPathToAction(
			std::shared_ptr<GoToGoal> goal,
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			std::weak_ptr<IAgent> agent,
			std::shared_ptr<Navigation::INavigationPlanner> navigationPlanner) :
			BaseAction(preConditions, postConditions, 0),
			mGoal { goal },
			mAgent {agent},
			mNavigationPlanner { navigationPlanner },
			mWaitingForPath {false}
		{
			mHasAccomplished = false;
		}

		void FindPathToAction::Process(float elapsedTime)
		{
			if(!mWaitingForPath)
			{
				auto placeName = GetPlaceToGo();
				auto destination = mNavigationPlanner->GetLocationGivenAName(placeName);
				if(auto agentPtr = mAgent.lock())
				{
					mWaitingForPath = true;
					mNavigationPlanner->GetPathFromTo(agentPtr->GetPosition(), destination,
						[this, placeName](std::shared_ptr<Navigation::INavigationPath> path)
						{
							if(auto goalPtr = mGoal.lock())
							{ 
								goalPtr->OnNavigationPath(placeName, path);
								mHasAccomplished = true;
							}
						});
				}
				else
				{
					//TODO ver como se cocina esto, igual puede devolver false
					//igual no hay que hacer nada pues si no se puede hacer un lock es que el objeto no existe???
					Cancel();
				}
			}
		}

		std::string FindPathToAction::GetPlaceToGo() const
		{
			//TODO presuponemos que las precondiciones y los matched predicates están en el mismo orden.
			//quizá se podrían relacionar para no tener que presuponer esto.
			auto goToPredicateMatch = GetPredicateMatchedPreconditionWithIndex(0);
			auto goToPredicate = std::static_pointer_cast<GoToPredicate>(goToPredicateMatch);

			return goToPredicate->GetPlaceName();
		}
	}
}
