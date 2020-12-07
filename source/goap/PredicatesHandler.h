#pragma once
#include "IPredicate.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class PredicatesHandler
		{		
		public:
			PredicatesHandler() = default;
			~PredicatesHandler() = default;

			const std::vector<std::shared_ptr<IPredicate>>& GetPredicatesList() const { return mPredicates; }
			std::vector<std::shared_ptr<IPredicate>>& GetPredicatesList() { return mPredicates; }
			void Add(const std::shared_ptr<IPredicate>& predicate);
			std::shared_ptr<IPredicate> FindByText(const std::string& predicateText) const;
			std::shared_ptr<IPredicate> FindById(int predicateId) const;

			void Reset(const std::vector<std::shared_ptr<IPredicate>>& predicates);

			private:
			std::vector<std::shared_ptr<IPredicate>> mPredicates;
		};
	}
}
