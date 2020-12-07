#pragma once
#include <string>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IPredicate
		{
		public:
			virtual ~IPredicate() = default;
			virtual int GetID() const = 0;
			virtual std::string GetText() const = 0;
			virtual std::string GetFullText() const = 0;
			//virtual bool Evaluate(const std::shared_ptr<IPredicate> predicate) = 0;
			virtual bool IsEqualTo(const std::shared_ptr<IPredicate> predicate) = 0;
		};
	}

}