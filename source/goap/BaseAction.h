#pragma once
#include "IAction.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class BaseAction : public IAction
		{
		public:
			BaseAction(
				const std::vector<std::shared_ptr<IPredicate>>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions,
				unsigned int cost = 0);
			virtual ~BaseAction() = default;

			const std::vector<std::shared_ptr<IPredicate>>& GetPreconditions() const override { return mPreConditions; }
			const std::vector<std::shared_ptr<IPredicate>>& GetPostconditions() const override { return mPostConditions; }
			unsigned int GetCost() const override { return mCost; }
			void Process(float elapsedTime) override;
			bool HasAccomplished() const override { return mHasAccomplished;}
			bool SatisfyPrecondition(std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			bool SatisfyPostcondition(std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			void Cancel() override;

		private:
			bool SatisfyConditions(
				std::vector<std::shared_ptr<IPredicate>>& conditions,
				std::vector<std::shared_ptr<IPredicate>>& predicates);

		private:
			std::vector<std::shared_ptr<IPredicate>> mPreConditions;
			std::vector<std::shared_ptr<IPredicate>> mPostConditions;
			unsigned int mCost;
			bool mHasAccomplished;
		};
	}
}
