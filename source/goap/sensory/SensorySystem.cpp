#include "pch.h"
#include "SensorySystem.h"
#include "IThreshold.h"
#include "IStimulus.h"

namespace NAI
{
	namespace Goap
	{
		SensorySystem::SensorySystem() :
		mStimulusReceived {},
		mStimulusPerceived {}
		{
		}

		void SensorySystem::Update(float elapsedTime, std::map<std::string, std::shared_ptr<IThreshold>> thresholds)
		{
			for(auto&& stimulus : mStimulusReceived)
			{
				const auto name = stimulus->GetClassName();
				auto it = thresholds.find(name);
				if(it != thresholds.end())
				{
					auto threshold = it->second;
					if(threshold->IsStimulusPerceived(stimulus))
					{
						mStimulusPerceived.push_back(stimulus);
					}
				}
			}
		}

		void SensorySystem::OnSensorNotification(std::shared_ptr<IStimulus> stimulus)
		{
			mStimulusReceived.push_back(stimulus);
		}
	}
}
