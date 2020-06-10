#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	class Predicate;

	class Action
	{
		std::vector<std::shared_ptr<Predicate>> mPreconditions;

	public:
		Action(std::vector<std::shared_ptr<Predicate>>& predicates);
		virtual ~Action() = default;

		std::vector<std::shared_ptr<Predicate>> GetPreconditions() const { return mPreconditions; }
	};
}
