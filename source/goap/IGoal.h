#pragma once
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IAction;
		class IPredicate;
		
		class IGoal
		{
		public:
			virtual ~IGoal() = default;
			virtual const std::vector<std::shared_ptr<IAction>>& GetActions() const = 0;
			virtual const unsigned int GetCost() const = 0;
			virtual bool SatisfyActions(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const = 0;
		};
	}
}

