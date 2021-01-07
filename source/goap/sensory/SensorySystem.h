#pragma once
#include <utils/subscriber/ISubscriber.h>
#include <vector>
#include <memory>
#include <map>
#include <string>

#include "goap/memory/Memory.h"
#include "goap/sensory/IStimulus.h"
#include "goap/sensory/IThreshold.h"

namespace NAI
{
	namespace Goap
	{
		template<class T>
		class SensorySystem : public core::utils::subscriber::ISubscriber<T>
		{
			const float RESIDENT_IN_MEMORY = 60.0f; // 1 min
			
		public:
			SensorySystem();
			virtual ~SensorySystem() = default;

			void Update(float elapsedTime, Memory<T>& shortTermMemory, std::map<std::string, std::shared_ptr<IThreshold>> thresholds);
			
			//ISubscriber inherited
			void OnNotification(std::shared_ptr<T> stimulus) override;

			//For test purposes
			std::vector<std::shared_ptr<T>> GetReceivedStimulus() const { return mStimulusReceived; }
			
		private:
			std::vector<std::shared_ptr<T>> mStimulusReceived;
		};

		template<class T>
		SensorySystem<T>::SensorySystem() :
			mStimulusReceived{}
		{
		}

		template<class T>
		void SensorySystem<T>::Update(float elapsedTime, Memory<T>& shortTermMemory, std::map<std::string, std::shared_ptr<IThreshold>> thresholds)
		{
			for (auto&& stimulus : mStimulusReceived)
			{
				const auto name = stimulus->GetClassName();
				auto it = thresholds.find(name);
				if (it != thresholds.end())
				{
					auto threshold = it->second;
					if (threshold->IsStimulusPerceived(stimulus))
					{
						shortTermMemory.Add(stimulus, RESIDENT_IN_MEMORY);
					}
				}
			}
		}

		template<class T>
		void SensorySystem<T>::OnNotification(std::shared_ptr<T> stimulus)
		{
			mStimulusReceived.push_back(stimulus);
		}
	}
}
