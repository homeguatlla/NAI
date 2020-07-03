#pragma once
#include "IGoal.h"

#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IAction;

		class BaseGoal : public IGoal, public std::enable_shared_from_this<BaseGoal>
		{
		public:
			BaseGoal() = default;
			BaseGoal(const std::vector<std::shared_ptr<IAction>>& actions);
			virtual ~BaseGoal() = default;

			const std::vector<std::shared_ptr<IAction>>& GetActions() const override { return mActions; }
			const unsigned int GetCost() const override { return mCost; }
			bool SatisfyActions(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) override;

		private:
			void CalculateCost();

		protected:
			std::vector<std::shared_ptr<IAction>> mActions;
			unsigned int mCost;
		};
	}
}

