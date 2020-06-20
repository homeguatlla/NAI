#include "pch.h"
#include "BaseGoal.h"
#include "IAction.h"

namespace NAI
{
	namespace Goap
	{
		BaseGoal::BaseGoal(const std::vector<std::shared_ptr<IAction>>& actions) : mActions{ actions }, mCost{ 0 }
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

		bool BaseGoal::SatisfyActions(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
		{
			bool satisfied = false;

			if (!inputPredicates.empty() && !mActions.empty())
			{
				std::vector<std::shared_ptr<IPredicate>> predicates = inputPredicates;
				std::vector<std::shared_ptr<IAction>> actions = mActions;

				int lastPredicatesSize = predicates.size();
				do
				{
					lastPredicatesSize = predicates.size();
					for (auto it = actions.begin(); it != actions.end();)
					{
						auto action = *it;
						if (action->SatisfyPrecondition(predicates))
						{
							auto postconditions = action->GetPostconditions();
							predicates.insert(end(predicates), begin(postconditions), end(postconditions));
							it = actions.erase(it);
						}
						else
						{
							it++;
						}
					}
				} while (static_cast<int>(predicates.size()) > lastPredicatesSize);

				satisfied = actions.empty();
			}

			return satisfied;
		}
	}
}
