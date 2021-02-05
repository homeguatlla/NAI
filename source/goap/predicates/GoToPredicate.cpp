#include "pch.h"
#include "GoToPredicate.h"
#include <glm/gtx/string_cast.hpp>

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

		GoToPredicate::GoToPredicate(int id, const std::string& text, const glm::vec3& location) : 
        BasePredicate(id, text),
		mPlaceName{glm::to_string(location)},
        mLocation{location}
		{
		}
		
		bool GoToPredicate::IsEqualTo(const std::shared_ptr<IPredicate> predicate)
		{
			return predicate->GetText().find(GetText()) != std::string::npos;
		}
	}
}