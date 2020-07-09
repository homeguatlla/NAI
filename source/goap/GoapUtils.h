#pragma once
#include "source/Goap/IPredicate.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class Utils
		{
		public:
			static std::vector<std::shared_ptr<IPredicate>> Concat(
				const std::vector<std::shared_ptr<IPredicate>>& v1,
				const std::vector<std::shared_ptr<IPredicate>>& v2)
			{
				std::vector<std::shared_ptr<IPredicate>> concat;

				concat = v1;
				concat.insert(concat.end(), v2.begin(), v2.end());

				return concat;
			}

			static std::vector<std::shared_ptr<IPredicate>> Substract(
				const std::vector<std::shared_ptr<IPredicate>>& v1,
				const std::vector<std::shared_ptr<IPredicate>>& v2)
			{
				std::vector<std::shared_ptr<IPredicate>> substraction;

				//TODO this operation can be of o(n+m) if both vectors are sorted.
				//https://stackoverflow.com/questions/21195217/elegant-way-to-remove-all-elements-of-a-vector-that-are-contained-in-another-vec

				substraction = v1;
				for (auto&& predicate : v2)
				{
					auto it = std::remove_if(substraction.begin(), substraction.end(), [predicate](std::shared_ptr<IPredicate> p) { return p->GetID() == predicate->GetID(); });
					substraction.erase(it);
				}
				return substraction;
			}
		};
	}
}

