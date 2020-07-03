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
			explicit GoToPredicate(const std::string& text, const std::string& placeName);
			~GoToPredicate() = default;

			bool IsEqualTo(const std::shared_ptr<IPredicate> predicate) override;
			std::string GetPlaceName() const { return mPlaceName; }

		private:
			std::string mPlaceName;
		};
	}
}
