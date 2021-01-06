#pragma once

#include <goap/memory/Memory.h>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class PerceptionSystem
		{		
		public:
			PerceptionSystem();
			~PerceptionSystem() = default;

			void Update(float elapsedTime);
		};
	}
}
