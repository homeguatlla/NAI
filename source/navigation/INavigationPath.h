#pragma once

#include <vector>
#include <memory>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPath
		{
		public:
			virtual ~INavigationPath() = default;
			virtual bool Empty() const  = 0;
		};
	}
}

