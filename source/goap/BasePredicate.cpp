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
	}
}