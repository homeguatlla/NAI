#pragma once
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class ISensorSubscriber
		{		
		public:
			virtual void OnSensorNotification() = 0;
		};
	}
}
