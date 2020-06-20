#pragma once

namespace NAI
{
	namespace Goap
	{
		class IPredicate
		{
		public:
			virtual ~IPredicate() = default;
			virtual int GetID() const = 0;
		};
	}

}