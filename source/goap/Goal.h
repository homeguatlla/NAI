#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	class Action;

	class Goal
	{
		std::vector<std::shared_ptr<Action>> mActions;

	public:
		Goal(const std::vector<std::shared_ptr<Action>>& actions);

		const std::vector<std::shared_ptr<Action>>& GetActions() const { return mActions; }
	};
}

