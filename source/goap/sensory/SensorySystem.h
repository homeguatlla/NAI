#pragma once
#include <utils/subscriber/ISubscriber.h>
#include <vector>
#include <memory>
#include <map>
#include <string>

#include "goap/memory/ShortTermMemory.h"
#include "goap/sensory/IStimulus.h"
#include "goap/sensory/IThreshold.h"

namespace NAI
{
	namespace Goap
	{
		template<class T>
		class SensorySystem : public core::utils::subscriber::ISubscriber<T>
		{
		public:
			SensorySystem();
			virtual ~SensorySystem() = default;

			void Update(float elapsedTime, ShortTermMemory<T>& shortTermMemory, std::map<std::string, std::shared_ptr<IThreshold>> thresholds);
			
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
		void SensorySystem<T>::Update(float elapsedTime, ShortTermMemory<T>& shortTermMemory, std::map<std::string, std::shared_ptr<IThreshold>> thresholds)
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
						//TODO hay que decidir si es un estímulo de tipo que se actualiza o no
						shortTermMemory.AddOrReplace(stimulus, stimulus->GetDurationInMemory());
					}
				}
			}
			mStimulusReceived.clear();
		}

		template<class T>
		void SensorySystem<T>::OnNotification(std::shared_ptr<T> stimulus)
		{
			mStimulusReceived.push_back(stimulus);
		}
	}
}
