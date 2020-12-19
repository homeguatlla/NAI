#pragma once
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IStimulus;
		
		class ISensorSubscriber
		{		
		public:
			virtual void OnSensorNotification(std::shared_ptr<IStimulus> stimulus) = 0;
		};
	}
}
