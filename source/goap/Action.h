#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	class Predicate;

	class Action
	{
	public:
		Action(
			const std::vector<std::shared_ptr<Predicate>>& preconditions,
			const std::vector<std::shared_ptr<Predicate>>& postconditions,
			unsigned int cost = 0);
		virtual ~Action() = default;

		const std::vector<std::shared_ptr<Predicate>>& GetPreconditions() const { return mPreconditions; }
		const std::vector<std::shared_ptr<Predicate>>& GetPostconditions() const { return mPostconditions; }
		unsigned int GetCost() const { return mCost; }

	private:
		std::vector<std::shared_ptr<Predicate>> mPreconditions;
		std::vector<std::shared_ptr<Predicate>> mPostconditions;
		unsigned int mCost;
	};
}
