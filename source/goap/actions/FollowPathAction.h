#pragma once
#include "source/goap/BaseAction.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace NAI
{
	namespace Goap
	{
		class FollowPathAction : public BaseAction
		{
		public:
			FollowPathAction(
				const std::vector<std::shared_ptr<IPredicate>>& preConditions,
				const std::vector<std::shared_ptr<IPredicate>>& postConditions,
				std::vector<glm::vec3>& path);
			virtual ~FollowPathAction() = default;

		private:
			std::vector<glm::vec3>& mPath;
		};
	}
}
