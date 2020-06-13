#pragma once
#include "IPredicate.h"
#include <string>

namespace NAI
{
	class BasePredicate : public IPredicate
	{
	public:
		explicit BasePredicate(const std::string& predicate);
		~BasePredicate() = default;

	private:
		std::string mText;
	};
}
