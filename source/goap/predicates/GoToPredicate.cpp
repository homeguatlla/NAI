#include "pch.h"
#include "GoToPredicate.h"

namespace NAI
{
	namespace Goap
	{
		GoToPredicate::GoToPredicate(int id, const std::string& text) : GoToPredicate(id, text, "")
		{
		}

		GoToPredicate::GoToPredicate(int id, const std::string& text, const std::string& placeName) : 
		BasePredicate(id, text),
		mPlaceName { placeName }
		{
		}

		GoToPredicate::GoToPredicate(int id, const std::string& text, const glm::vec3& position) : 
        BasePredicate(id, text),
        mPosition{position}
		{
		}
		
		bool GoToPredicate::IsEqualTo(const std::shared_ptr<IPredicate> predicate)
		{
			return predicate->GetText().find(GetText()) != std::string::npos;
		}
	}
}