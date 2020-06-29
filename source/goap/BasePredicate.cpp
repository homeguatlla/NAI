#include "pch.h"
#include "BasePredicate.h"

namespace NAI
{
	namespace Goap
	{
		int BasePredicate::IDCounter = 0;

		BasePredicate::BasePredicate(const std::string& text) : mID{ IDCounter++ }, mText {text}
		{
		}

		bool BasePredicate::IsEqualTo(const std::shared_ptr<IPredicate>& predicate)
		{
			return GetID() == predicate->GetID();
		}
	}
}