#pragma once
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IPredicate;

		class IAction
		{
		public:
			virtual ~IAction() = default;

			virtual const std::vector<std::shared_ptr<IPredicate>>& GetPreconditions() const = 0;
			virtual const std::vector<std::shared_ptr<IPredicate>>& GetPostconditions() const = 0;
			virtual unsigned int GetCost() const = 0;
			virtual void Process(float elapsedTime) = 0;
			virtual bool HasAccomplished() const = 0;
			virtual bool SatisfyPrecondition(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			virtual bool SatisfyPostcondition(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			//This both methods return the list of predicates that satisfy post and pre conditions. If is not satisfied, the returned value is an empty vector
			virtual std::vector<std::shared_ptr<IPredicate>> GetPredicatesSatisfyPostconditions(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			virtual std::vector<std::shared_ptr<IPredicate>> GetPredicatesSatisfyPreconditions(std::vector<std::shared_ptr<IPredicate>>& predicates) = 0;
			virtual void Cancel() = 0;
		};
	}
}
