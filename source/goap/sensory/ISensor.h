#pragma once
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class ISensorSubscriber;
		
		class ISensor
		{		
		public:
			virtual ~ISensor() = default;
			virtual void Subscribe(const std::shared_ptr<ISensorSubscriber> subscriber) = 0;
			virtual void Update(float elapsedTime) = 0;
		};
	}
}
