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
			virtual const unsigned int GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const = 0;
			virtual bool SatisfyActions(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) = 0;
			virtual void Accomplished(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			virtual void Cancel() = 0;
			virtual std::vector<std::shared_ptr<IPredicate>> GetPredicatesCanBeAccomplished(std::vector<std::shared_ptr<IPredicate>> desiredPredicates) = 0;
			virtual std::vector<std::shared_ptr<IPredicate>> GetPredicatesSatisfyPreconditions(std::vector<std::shared_ptr<IPredicate>> inputPredicates) = 0;
		};
	}
}

