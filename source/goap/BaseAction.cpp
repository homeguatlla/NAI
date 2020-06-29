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
			return SatisfyConditions(mPreConditions, predicates);
		}

		bool BaseAction::SatisfyPostcondition(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			return SatisfyConditions(mPostConditions, predicates);
		}

		bool BaseAction::SatisfyConditions(
		std::vector<std::shared_ptr<IPredicate>>& conditions, 
		std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			return std::all_of(conditions.begin(), conditions.end(),
				[&predicates](std::shared_ptr<IPredicate> predicateA)
				{
					return std::find_if(predicates.begin(), predicates.end(),
						[predicateA](std::shared_ptr<IPredicate> predicateB)
						{
							return predicateA->IsEqualTo(predicateB);
						}) != predicates.end();
				});
		}

		void BaseAction::Cancel()
		{
		}
	}
}
