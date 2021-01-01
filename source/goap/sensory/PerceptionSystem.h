#pragma once

#include <goap/memory/Memory.h>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IStimulus;
		
		class PerceptionSystem
		{		
		public:
			PerceptionSystem();
			~PerceptionSystem() = default;

			void Update(float elapsedTime, Memory<std::shared_ptr<IStimulus>>& memory);
		};
	}
}
