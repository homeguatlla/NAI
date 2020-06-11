#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	class Predicate;

	class Action
	{
		std::vector<std::shared_ptr<Predicate>> mPreconditions;
		std::vector<std::shared_ptr<Predicate>> mPostconditions;

	public:
		Action(const std::vector<std::shared_ptr<Predicate>>& preconditions, const std::vector<std::shared_ptr<Predicate>>& postconditions);
		virtual ~Action() = default;

		const std::vector<std::shared_ptr<Predicate>>& GetPreconditions() const { return mPreconditions; }
		const std::vector<std::shared_ptr<Predicate>>& GetPostconditions() const { return mPostconditions; }
	};
}
