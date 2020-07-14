#pragma once

#include <vector>
#include <memory>
#include <functional>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPath;

		class INavigationPlanner
		{
		public:
			virtual ~INavigationPlanner() = default;
			virtual void GetPathFromTo(const glm::vec3& origin, const glm::vec3& destination, std::function<void(std::shared_ptr<INavigationPath>)> callback) const = 0;
			virtual glm::vec3 GetLocationGivenAName(const std::string& locationName) const = 0;
			virtual unsigned int GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const = 0;
		};
	}
}

