#pragma once
#include "ISensorSubscriber.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

#include "goap/memory/Memory.h"

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

			void Update(float elapsedTime, std::map<std::string, std::shared_ptr<IThreshold>> thresholds);
			
			//ISensorSubscriber inherited
			void OnSensorNotification(std::shared_ptr<IStimulus> stimulus) override;

			//For test purposes
			bool IsMemoryEmpty() const { return mShortTermMemory.IsEmpty(); }
			std::vector<std::shared_ptr<IStimulus>> GetReceivedStimulus() const { return mStimulusReceived; }
			
		private:
			std::vector<std::shared_ptr<IStimulus>> mStimulusReceived;
			Memory<IStimulus> mShortTermMemory;
		};
	}
}
