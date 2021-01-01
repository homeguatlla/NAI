#pragma once
#include <utils/subscriber/BasePublisher.h>
#include "ISensor.h"

namespace NAI
{
	namespace Goap
	{
		class IStimulus;
		
		class BaseSensor : public core::utils::subscriber::BasePublisher<IStimulus>, public ISensor
		{		
		public:
			BaseSensor() = default;
			virtual ~BaseSensor() = default;
		};
	}
}
