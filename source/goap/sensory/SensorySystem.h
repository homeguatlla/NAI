#pragma once
#include "ISensorSuscriber.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

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
			void Update(float elapsedTime, std::map<std::string, std::shared_ptr<IThreshold>> thresholds);
			
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
