#include "pch.h"
#include "PredicatesHandler.h"

namespace NAI
{
	namespace Goap
	{
		void PredicatesHandler::AddOrReplace(const std::shared_ptr<IPredicate>& predicate)
		{
			auto it = std::find_if(mPredicates.begin(), mPredicates.end(),
                [predicate](const std::shared_ptr<IPredicate>& p)
                {
                    return p->GetText() == predicate->GetText();
                });
			if(it == mPredicates.end())
			{
				mPredicates.push_back(predicate);
			}
			else
			{
				*it = predicate;
			}
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