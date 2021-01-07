#pragma once

#include <goap/memory/Memory.h>

#include "CognitiveSystem.h"
#include "SensorySystem.h"

namespace NAI
{
	namespace Goap
	{
		class IStimulus;
		class CognitiveSystem;
		
		class PerceptionSystem
		{		
		public:
			PerceptionSystem(std::shared_ptr<SensorySystem<IStimulus>> sensorySystem);
			virtual ~PerceptionSystem() = default;

			Memory<IStimulus>& GetMemory() { return mMemory; }
			void Update(float elapsedTime, std::shared_ptr<IAgent> agent);

		private:
			void CreateCognitiveSystem();
		
		private:
			Memory<IStimulus> mMemory;
			std::shared_ptr<SensorySystem<IStimulus>> mSensorySystem;
			std::shared_ptr<CognitiveSystem> mCognitiveSystem;
		};
	}
}
