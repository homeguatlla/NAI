#pragma once
#include "ISensorSuscriber.h"
#include <vector>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IStimulus;
		class IThreshold;
		
		class SensorySystem : public ISensorSubscriber
		{		
		public:
			SensorySystem();
			~SensorySystem() = default;

			std::vector<std::shared_ptr<IStimulus>> GetPerceivedStimulus() const { return mStimulusPerceived; }
			void Update(float elapsedTime, std::shared_ptr<IThreshold> threshold);
			
			//ISensorSubscriber inherited
			void OnSensorNotification(std::shared_ptr<IStimulus> stimulus) override;

			//For test purposes
			std::vector<std::shared_ptr<IStimulus>> GetReceivedStimulus() const { return mStimulusReceived; }
		private:
			std::vector<std::shared_ptr<IStimulus>> mStimulusReceived;
			std::vector<std::shared_ptr<IStimulus>> mStimulusPerceived;
		};
	}
}
