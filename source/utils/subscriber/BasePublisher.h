#pragma once

#include "IPublisher.h"
#include "ISubscriber.h"
#include <vector>
#include <memory>

namespace core
{
	namespace utils
	{
		namespace subscriber
		{
			template<class T>
			class BasePublisher : public IPublisher<T>
			{
			public:
				BasePublisher() = default;
				virtual ~BasePublisher() = default;

				bool Subscribe(std::shared_ptr<ISubscriber<T>> subscriber) override;
				bool UnSubscribe(std::shared_ptr<ISubscriber<T>> subscriber) override;
				void NotifyAll(std::shared_ptr<T> event) override;
				
				//Test purposes
				bool HasSubscribers() const { return !mSubscribers.empty(); }
			private:
				std::vector<std::shared_ptr<ISubscriber<T>>> mSubscribers;
			};

			template<class T>
			bool BasePublisher<T>::Subscribe(std::shared_ptr<ISubscriber<T>> subscriber)
			{
				auto found = std::find(mSubscribers.begin(), mSubscribers.end(), subscriber) != mSubscribers.end();

				if(!found)
				{
					mSubscribers.push_back(subscriber);
				}
				
				return !found;
			}

			template<class T>
			bool BasePublisher<T>::UnSubscribe(std::shared_ptr<ISubscriber<T>> subscriber)
			{
				const auto it = std::find(mSubscribers.begin(), mSubscribers.end(), subscriber);

				const auto found = it != mSubscribers.end();
				if (found)
				{
					mSubscribers.erase(it);
				}
				
				return found;
			}

			template<class T>
			void BasePublisher<T>::NotifyAll(std::shared_ptr<T> event)
			{
				for(auto&& subscriber : mSubscribers)
				{
					subscriber->OnNotification(event);
				}
			}
		}
	}
}

