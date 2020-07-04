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
			virtual std::shared_ptr<IAction> GetNextAction() = 0;
			virtual bool HasActions() const = 0;
			virtual const unsigned int GetCost() const = 0;
			virtual bool SatisfyActions(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) = 0;
		};
	}
}

