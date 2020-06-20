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
			mCost{ cost }
		{
		}

		void BaseAction::Process(float elapsedTime)
		{

		}

		bool BaseAction::SatisfyPrecondition(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			return std::all_of(mPreConditions.begin(), mPreConditions.end(), 
			[&predicates](std::shared_ptr<IPredicate> predicateA) 
			{
				return std::find_if(predicates.begin(), predicates.end(), 
				[predicateA](std::shared_ptr<IPredicate> predicateB)
				{
					return predicateA->GetID() == predicateB->GetID();
				}) != predicates.end();
			});
		}
	}
}
