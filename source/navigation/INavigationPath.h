#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPath
		{
		public:
			virtual ~INavigationPath() = default;
			virtual bool Empty() const  = 0;
			virtual bool HasReachedPoint(int index, const glm::vec3& position, float precision) const = 0;
			virtual glm::vec3 GetPoint(int index) const = 0;
			virtual bool IsEndOfPath(int index) const = 0;
		};
	}
}

