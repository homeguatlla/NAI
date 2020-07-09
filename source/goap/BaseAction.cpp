#include "pch.h"
#include "BaseAction.h"
#include "IPredicate.h"
#include <algorithm>

namespace NAI
{
	namespace Goap
	{
		BaseAction::BaseAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			unsigned int cost) :
			mPreConditions{ preConditions },
			mPostConditions{ postConditions },
			mCost{ cost },
			mHasAccomplished { true }
		{
		}

		void BaseAction::Process(float elapsedTime)
		{
		}

		bool BaseAction::SatisfyPrecondition(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			ResetMatchedPreConditions();
			mMatchedPreConditions = SatisfyConditions(mPreConditions, predicates);

			return !mMatchedPreConditions.empty();
		}

		bool BaseAction::SatisfyPostcondition(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			return !SatisfyConditions(mPostConditions, predicates).empty();
		}

		std::vector<std::shared_ptr<IPredicate>> BaseAction::GetPredicatesSatisfyPostconditions(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			return SatisfyConditions(mPostConditions, predicates);
		}

		std::vector<std::shared_ptr<IPredicate>> BaseAction::SatisfyConditions(
		std::vector<std::shared_ptr<IPredicate>>& conditions, 
		std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			std::vector<std::shared_ptr<IPredicate>> result;

			std::all_of(conditions.begin(), conditions.end(),
				[&result, &predicates](std::shared_ptr<IPredicate> predicateA)
				{
					auto it = std::find_if(predicates.begin(), predicates.end(),
						[predicateA](std::shared_ptr<IPredicate> predicateB)
						{
							return predicateA->IsEqualTo(predicateB);
						});

					bool satisfy = it != predicates.end();
					if (satisfy)
					{
						result.push_back(*it);
					}

					return satisfy;
				});

			return result;
		}

		void BaseAction::ResetMatchedPreConditions()
		{
			mMatchedPreConditions.clear();
		}

		void BaseAction::Cancel()
		{
		}
	}
}
