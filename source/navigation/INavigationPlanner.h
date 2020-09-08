#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <glm/glm.hpp>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPath;

		class INavigationPlanner
		{
		public:
			using PathFromToCallback = std::function<void(std::shared_ptr<NAI::Navigation::INavigationPath>)>;

			virtual ~INavigationPlanner() = default;
			virtual void GetPathFromTo(const glm::vec3& origin, const glm::vec3& destination, PathFromToCallback callback) = 0;
			virtual glm::vec3 GetLocationGivenAName(const std::string& locationName) const = 0;
			virtual unsigned int GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const = 0;
		};
	}
}

