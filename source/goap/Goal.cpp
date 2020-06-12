#include "pch.h"
#include "Goal.h"
#include "Action.h"

namespace NAI
{
	Goal::Goal(const std::vector<std::shared_ptr<Action>>& actions) : mActions{ actions }, mCost {0}
	{
		CalculateCost();
	}

	void Goal::CalculateCost()
	{
		for (auto&& action : mActions)
		{
			mCost += action->GetCost();
		}
	}

}
