#include "pch.h"
#include "PlaceIamPredicate.h"

namespace NAI
{
	namespace Goap
	{
		PlaceIamPredicate::PlaceIamPredicate(int id, const std::string& text) : PlaceIamPredicate(id, text, "")
		{
		}

		PlaceIamPredicate::PlaceIamPredicate(int id, const std::string& text, const std::string& placeName) :
		BasePredicate(id, text),
		mPlaceName { placeName }
		{
		}

		bool PlaceIamPredicate::IsEqualTo(const std::shared_ptr<IPredicate> predicate)
		{
			return predicate->GetText().find(GetText()) != std::string::npos;
		}
	}
}