#pragma once
#include <memory>

namespace core
{
	namespace utils
	{
		namespace subscriber
		{
			template<class T>
			class ISubscriber
			{		
			public:
				virtual void OnNotification(std::shared_ptr<T>) = 0;
			};
		}
	}
}
