#pragma once
#include "goap/BasePredicate.h"
#include <glm/glm.hpp>


namespace NAI
{
	namespace Goap
	{
		class GoToPredicate : public BasePredicate
		{
		public:
			explicit GoToPredicate(int id, const std::string& text);
			explicit GoToPredicate(int id, const std::string& text, const std::string& placeName);
			explicit GoToPredicate(int id, const std::string& text, const glm::vec3& location);

			~GoToPredicate() = default;

			bool IsEqualTo(const std::shared_ptr<IPredicate> predicate) override;
			std::string GetPlaceName() const { return mPlaceName; }
			std::string GetFullText() const override { return GetText() + " " + mPlaceName; }
			glm::vec3 GetLocation() const { return mLocation; }

		private:
			std::string mPlaceName;
			glm::vec3 mLocation;
		};
	}
}
