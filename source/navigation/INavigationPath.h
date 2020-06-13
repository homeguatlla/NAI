#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	class IAction;

	class IGoal
	{
	public:
		virtual ~IGoal() = default;
		virtual const std::vector<std::shared_ptr<IAction>>& GetActions() const = 0;
		virtual const unsigned int GetCost() const = 0;
	};
}

