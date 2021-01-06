#include "pch.h"
#include "GoToPredicate.h"

namespace NAI
{
	namespace Goap
	{
		GoToPredicate::GoToPredicate(const std::string& text) : GoToPredicate(text, "")
		{
		}

		GoToPredicate::GoToPredicate(const std::string& text, const std::string& placeName) : 
		BasePredicate(text),
		mPlaceName { placeName }
		{
		}

		GoToPredicate::GoToPredicate(const std::string& text, const glm::vec3& position) : 
        BasePredicate(text),
        mPosition{position}
		{
		}
		
		bool GoToPredicate::IsEqualTo(const std::shared_ptr<IPredicate> predicate)
		{
			return predicate->GetText().find(GetText()) != std::string::npos;
		}
	}
}