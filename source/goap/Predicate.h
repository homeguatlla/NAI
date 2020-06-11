#pragma once
#include <string>

namespace NAI
{
	class Predicate
	{
		std::string mText;

	public:
		explicit Predicate(const std::string& predicate);
		~Predicate() = default;
	};
}
