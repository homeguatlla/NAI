#pragma once
#include "source/goap/BasePredicate.h"

namespace NAI
{
	namespace Goap
	{
		class GoToPredicate : public BasePredicate
		{
		public:
			explicit GoToPredicate(const std::string& text);
			~GoToPredicate() = default;

			bool IsEqualTo(const std::shared_ptr<IPredicate>& predicate) override;
		};
	}
}
