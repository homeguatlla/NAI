#pragma once
#include "IAction.h"
#include <vector>
#include <memory>

namespace NAI
{
	class IPredicate;

	class BaseAction : public IAction
	{
	public:
		BaseAction(
			const std::vector<std::shared_ptr<IPredicate>>& preconditions,
			const std::vector<std::shared_ptr<IPredicate>>& postconditions,
			unsigned int cost = 0);
		virtual ~BaseAction() = default;

		const std::vector<std::shared_ptr<IPredicate>>& GetPreconditions() const override { return mPreconditions; }
		const std::vector<std::shared_ptr<IPredicate>>& GetPostconditions() const override { return mPostconditions; }
		unsigned int GetCost() const override { return mCost; }

	private:
		std::vector<std::shared_ptr<IPredicate>> mPreconditions;
		std::vector<std::shared_ptr<IPredicate>> mPostconditions;
		unsigned int mCost;
	};
}
