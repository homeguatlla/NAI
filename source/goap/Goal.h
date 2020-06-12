#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	class Action;

	class Goal
	{
	public:
		Goal(const std::vector<std::shared_ptr<Action>>& actions);

		const std::vector<std::shared_ptr<Action>>& GetActions() const { return mActions; }
		const unsigned int GetCost() const { return mCost; }

	private:
		void CalculateCost();

	private:
		std::vector<std::shared_ptr<Action>> mActions;
		unsigned int mCost;
	};
}

