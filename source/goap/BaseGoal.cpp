#include "pch.h"
#include "BaseGoal.h"
#include "IAction.h"

namespace NAI
{
	namespace Goap
	{
		BaseGoal::BaseGoal(const std::vector<std::shared_ptr<IAction>>& actions) : mActions{ actions }, mCost{ 0 }
		{
			CalculateCost();
		}

		void BaseGoal::CalculateCost()
		{
			for (auto&& action : mActions)
			{
				mCost += action->GetCost();
			}
		}
	}
}
