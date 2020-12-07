#include "pch.h"
#include "PredicatesHandler.h"

namespace NAI
{
	namespace Goap
	{
		void PredicatesHandler::Add(const std::shared_ptr<IPredicate>& predicate)
		{
			mPredicates.push_back(predicate);
		}

		std::shared_ptr<IPredicate> PredicatesHandler::FindByText(const std::string& predicateText) const
		{
			const auto it = std::find_if(mPredicates.begin(), mPredicates.end(),
				[predicateText](const std::shared_ptr<IPredicate>& predicate)
				{
					return predicate->GetText() == predicateText;
				});
			
			return it != mPredicates.end() ? *it : nullptr;
		}

		std::shared_ptr<IPredicate> PredicatesHandler::FindById(int predicateId) const
		{
			const auto it = std::find_if(mPredicates.begin(), mPredicates.end(),
				[predicateId](const std::shared_ptr<IPredicate>& predicate)
				{
					return predicate->GetID() == predicateId;
				});


			return it != mPredicates.end() ? *it : nullptr;
		}

		void PredicatesHandler::Reset(const std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			mPredicates = predicates;
		}
	}
}