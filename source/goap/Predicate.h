#pragma once
#include <string>

namespace NAI
{
	class Predicate
	{
	public:
		explicit Predicate(const std::string& predicate);
		~Predicate() = default;

	private:
		std::string mText;
	};
}
