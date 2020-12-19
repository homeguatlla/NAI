#include "pch.h"
#include "SensorySystem.h"
#include "IThreshold.h"

namespace NAI
{
	namespace Goap
	{
		SensorySystem::SensorySystem() :
		mStimulusReceived {},
		mStimulusPerceived {}
		{
		}

		void SensorySystem::Update(float elapsedTime, std::shared_ptr<IThreshold> threshold)
		{
			for(auto&& stimulus : mStimulusReceived)
			{
				if(threshold->IsStimulusPerceived(stimulus))
				{
					mStimulusPerceived.push_back(stimulus);
				}
			}
		}

		void SensorySystem::OnSensorNotification(std::shared_ptr<IStimulus> stimulus)
		{
			mStimulusReceived.push_back(stimulus);
		}
	}
}
