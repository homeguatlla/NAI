#include "pch.h"
#include "GoToPredicate.h"

namespace NAI
{
	namespace Goap
	{
		GoToPredicate::GoToPredicate(const std::string& text) : BasePredicate(text)
		{

		}

		bool GoToPredicate::IsEqualTo(const std::shared_ptr<IPredicate>& predicate)
		{
			return predicate->GetText().find(GetText()) != std::string::npos;
		}
	}
}