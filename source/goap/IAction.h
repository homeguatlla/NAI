#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	class IPredicate;

	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual const std::vector<std::shared_ptr<IPredicate>>& GetPreconditions() const = 0;
		virtual const std::vector<std::shared_ptr<IPredicate>>& GetPostconditions() const = 0;
		virtual unsigned int GetCost() const = 0;
	};
}
