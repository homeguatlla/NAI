#include "pch.h"
#include "BaseGoal.h"
#include "IAction.h"
#include "GoapUtils.h"
#include <algorithm>

namespace NAI
{
	namespace Goap
	{
		BaseGoal::BaseGoal() :
			mCurrentActionIndex{ 0 },
			mCost{ 0 }
		{

		}

		BaseGoal::BaseGoal(const std::vector<std::shared_ptr<IAction>>& actions) : 
			mActions{ actions }, 
			mCurrentActionIndex { 0 } , 
			mCost{ 0 }
		{
			CalculateCost();
		}

		void BaseGoal::CalculateCost()
		{
			for (auto&& action : mActions)
			{
				mCost += action->GetCost();
			}
		}

		std::shared_ptr<IAction> BaseGoal::GetNextAction()
		{
			return HasActions() ? mActions[mCurrentActionIndex++] : nullptr;
		}

		bool BaseGoal::SatisfyActions(std::vector<std::shared_ptr<IPredicate>>& inputPredicates)
		{
			bool satisfied = false;

			if (!inputPredicates.empty() && !mActions.empty())
			{
				std::vector<std::shared_ptr<IPredicate>> predicates = inputPredicates;
				std::vector<std::shared_ptr<IAction>> actions;

				actions.swap(mActions);

				int lastPredicatesSize = predicates.size();
				do
				{
					lastPredicatesSize = predicates.size();
					for (auto it = actions.begin(); it != actions.end();)
					{
						auto action = *it;
						if (action->SatisfyPostcondition(predicates))
						{
							it = actions.erase(it);
						}
						else if (action->SatisfyPrecondition(predicates))
						{
							auto postconditions = action->GetPostconditions();
							predicates.insert(end(predicates), begin(postconditions), end(postconditions));
							mActions.push_back(action);
							it = actions.erase(it);
						}
						else
						{
							it++;
						}
					}
				} while (static_cast<int>(predicates.size()) > lastPredicatesSize);

				satisfied = actions.empty() && !mActions.empty();
			}

			return satisfied;
		}

		void BaseGoal::Cancel()
		{
			if(HasActions())
			{
				mActions[mCurrentActionIndex]->Cancel();
			}

			mCurrentActionIndex = 0;
			
			DoCancel();
		}

		std::vector<std::shared_ptr<IPredicate>> BaseGoal::GetPredicatesCanBeAccomplished(
			std::vector<std::shared_ptr<IPredicate>>& desiredPredicates)
		{
			std::vector<std::shared_ptr<IPredicate>> result;

			if(!desiredPredicates.empty())
			{
				for (auto&& action : mActions)
				{
					auto accomplishedPredicates = action->GetPredicatesSatisfyPostconditions(desiredPredicates);
					if (!accomplishedPredicates.empty())
					{
						result = Utils::Concat(result, accomplishedPredicates);
					}
				}
			}

			return result;
		}
	}
}
