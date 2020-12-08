#pragma once
#include "goap/BasePredicate.h"

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
			std::string GetFullText() const override { return GetText() + " " + mPlaceName; }

		private:
			std::string mPlaceName;
		};
	}
}
