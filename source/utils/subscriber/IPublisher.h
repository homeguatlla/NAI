#pragma once
#include <memory>

namespace core
{
	namespace utils
	{
		namespace subscriber
		{
			template<class T>
			class ISubscriber;

			template<class T>
			class IPublisher
			{		
			public:
				virtual ~IPublisher() = default;
				virtual bool Subscribe(std::shared_ptr<ISubscriber<T>> subscriber) = 0;
				virtual bool UnSubscribe(std::shared_ptr<ISubscriber<T>> subscriber) = 0;
				virtual void NotifyAll(std::shared_ptr<T> event) = 0;
			};
		}
	}
}