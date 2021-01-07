#include "pch.h"
#include "PerceptionSystem.h"
#include "CognitiveSystem.h"
#include "goap/agent/IAgent.h"

namespace NAI
{
	namespace Goap
	{
		PerceptionSystem::PerceptionSystem(std::shared_ptr<SensorySystem<IStimulus>> sensorySystem) :
		mSensorySystem{sensorySystem}
		{
			CreateCognitiveSystem();
		}

		void PerceptionSystem::Update(float elapsedTime, std::shared_ptr<IAgent> agent)
		{
			mSensorySystem->Update(elapsedTime, mMemory, agent->GetSensoryThresholds());
			mCognitiveSystem->Update(elapsedTime, mMemory, agent);
		}

		void PerceptionSystem::CreateCognitiveSystem()
		{
			mCognitiveSystem = std::make_shared<CognitiveSystem>();
		}
	}
}
