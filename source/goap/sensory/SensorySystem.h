#pragma once
#include <utils/subscriber/ISubscriber.h>
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

		template<class T>
		class SensorySystem : public core::utils::subscriber::ISubscriber<T>
		{
			const float RESIDENT_IN_MEMORY = 60.0f; // 1 min
			
		public:
			SensorySystem();
			~SensorySystem() = default;

			void Update(float elapsedTime, std::map<std::string, std::shared_ptr<IThreshold>> thresholds);
			
			//ISubscriber inherited
			void OnNotification(std::shared_ptr<T> stimulus) override;

			//For test purposes
			bool IsMemoryEmpty() const { return mShortTermMemory.IsEmpty(); }
			std::vector<std::shared_ptr<T>> GetReceivedStimulus() const { return mStimulusReceived; }
			
		private:
			std::vector<std::shared_ptr<T>> mStimulusReceived;
			Memory<T> mShortTermMemory;
		};

		template<class T>
		SensorySystem<T>::SensorySystem() :
			mStimulusReceived{},
			mShortTermMemory{}
		{
		}

		template<class T>
		void SensorySystem<T>::Update(float elapsedTime, std::map<std::string, std::shared_ptr<IThreshold>> thresholds)
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
						mShortTermMemory.Add(stimulus, RESIDENT_IN_MEMORY);
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
