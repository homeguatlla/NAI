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
			bool SatisfyPrecondition(const std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			bool SatisfyPostcondition(const std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			std::vector<std::shared_ptr<IPredicate>> GetPredicatesSatisfyPostconditions(const std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			std::vector<std::shared_ptr<IPredicate>> GetPredicatesSatisfyPreconditions(const std::vector<std::shared_ptr<IPredicate>>& predicates) override;
			void Cancel() override;
			const std::shared_ptr<IPredicate>& GetPredicateMatchedPreconditionWithIndex(unsigned int index) const { return mMatchedPreConditions[index]; }
			
		private:
			std::vector<std::shared_ptr<IPredicate>> SatisfyConditions(
				const std::vector<std::shared_ptr<IPredicate>>& conditions,
				const std::vector<std::shared_ptr<IPredicate>>& predicates);
			void ResetMatchedPreConditions();

		private:
			std::vector<std::shared_ptr<IPredicate>> mPreConditions;
			std::vector<std::shared_ptr<IPredicate>> mPostConditions;
			std::vector<std::shared_ptr<IPredicate>> mMatchedPreConditions;
			unsigned int mCost;

		protected:
			bool mHasAccomplished;
		};
	}
}
