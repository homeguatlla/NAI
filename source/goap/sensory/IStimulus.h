#pragma once
#include <glm/glm.hpp>

namespace NAI
{
	namespace Goap
	{
		class IStimulus
		{		
		public:
			virtual std::string GetClassName() const = 0;
			virtual glm::vec3 GetPosition() const = 0;
		};
	}
}
