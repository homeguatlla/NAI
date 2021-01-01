#pragma once

#include <goap/memory/Memory.h>
#include <memory>
#include <vector>

namespace NAI
{
	namespace Goap
	{
		class IStimulus;
		class IAgent;
		
		class PerceptionSystem
		{		
		public:
			PerceptionSystem();
			~PerceptionSystem() = default;

			void Update(
				float elapsedTime, 
				Memory<IStimulus>& memory, 
				std::shared_ptr<IAgent> agent);
		};
	}
}
