#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "memory/ShortTermMemory.h"

namespace NAI
{
	namespace Goap
	{
		class IAction;
		class IPredicate;
		class IAgent;
		class IStimulus;
		
		class IGoal
		{
		public:
			virtual ~IGoal() = default;
			virtual void Create(std::shared_ptr<IAgent> agent) = 0;
			virtual std::shared_ptr<IAction> GetNextAction() = 0;
			virtual bool HasActions() const = 0;
			virtual unsigned int GetCost() const = 0;
			virtual unsigned int GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const = 0;
			virtual bool SatisfyActions(const std::vector<std::shared_ptr<IPredicate>>& inputPredicates) = 0;
			virtual void Accomplished(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			virtual void Cancel(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			virtual void Reset(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			virtual std::vector<std::shared_ptr<IPredicate>> GetPredicatesCanBeAccomplished(std::vector<std::shared_ptr<IPredicate>> desiredPredicates) = 0;
			virtual std::vector<std::shared_ptr<IPredicate>> GetPredicatesSatisfyPreconditions(std::vector<std::shared_ptr<IPredicate>> inputPredicates) = 0;
			virtual std::shared_ptr<IPredicate> TransformStimulusIntoPredicates(const ShortTermMemory<IStimulus>& memory) const = 0;
		};
	}
}

