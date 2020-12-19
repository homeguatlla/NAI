#pragma once
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class IStimulus;
		
		class IThreshold
		{		
		public:
			virtual bool IsStimulusPerceived(std::shared_ptr<IStimulus> stimulus) const = 0;
		};
	}
}
