#include "pch.h"
#include "BasePredicate.h"

namespace NAI
{
	namespace Goap
	{
		BasePredicate::BasePredicate(int id, const std::string& text) : mID{ id }, mText {text}
		{
		}

		bool BasePredicate::IsEqualTo(const std::shared_ptr<IPredicate> predicate)
		{
			return mText == predicate->GetText(); //TODO ID quizá no hace falta pues?? igual solo para los test?. //GetID() == predicate->GetID();
		}
	}
}