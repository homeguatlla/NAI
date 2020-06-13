#pragma once
#include "IGoal.h"

#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IAction;

		class BaseGoal : public IGoal
		{
		public:
			BaseGoal(const std::vector<std::shared_ptr<IAction>>& actions);
			virtual ~BaseGoal() = default;

			const std::vector<std::shared_ptr<IAction>>& GetActions() const override { return mActions; }
			const unsigned int GetCost() const override { return mCost; }

		private:
			void CalculateCost();

		private:
			std::vector<std::shared_ptr<IAction>> mActions;
			unsigned int mCost;
		};
	}
}

