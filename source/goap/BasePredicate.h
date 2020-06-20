#pragma once
#include "IPredicate.h"
#include <string>

namespace NAI
{
	namespace Goap
	{
		class BasePredicate : public IPredicate
		{
		public:
			explicit BasePredicate(const std::string& text);
			~BasePredicate() = default;
			int GetID() const override { return mID; }
		private:
			int mID;
			std::string mText;
		};
	}
}
