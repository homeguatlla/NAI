#include "pch.h"
#include "PlaceIamPredicate.h"

namespace NAI
{
	namespace Goap
	{
		PlaceIamPredicate::PlaceIamPredicate(const std::string& text) : PlaceIamPredicate(text, "")
		{
		}

		PlaceIamPredicate::PlaceIamPredicate(const std::string& text, const std::string& placeName) :
		BasePredicate(text),
		mPlaceName { placeName }
		{
		}

		bool PlaceIamPredicate::IsEqualTo(const std::shared_ptr<IPredicate> predicate)
		{
			return predicate->GetText().find(GetText()) != std::string::npos;
		}
	}
}