#pragma once
#include "source/goap/BasePredicate.h"

namespace NAI
{
	namespace Goap
	{
		class PlaceIamPredicate : public BasePredicate
		{
		public:
			explicit PlaceIamPredicate(const std::string& text);
			explicit PlaceIamPredicate(const std::string& text, const std::string& placeName);
			~PlaceIamPredicate() = default;

			bool IsEqualTo(const std::shared_ptr<IPredicate> predicate) override;
			std::string GetPlaceName() const { return mPlaceName; }
			inline std::string GetFullText() const override { return GetText() + " " + mPlaceName; }

		private:
			std::string mPlaceName;
		};
	}
}
