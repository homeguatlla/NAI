#pragma once
#include <glm/glm_hpp.h>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPoint
		{
		public:
			virtual ~INavigationPoint() = default;
			virtual glm::vec3 GetOrigin() const = 0;
			virtual glm::vec3 GetDestination() const = 0;
		};
	}
}

