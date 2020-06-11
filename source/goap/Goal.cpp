#include "pch.h"
#include "Goal.h"

namespace NAI
{
	NAI::Goal::Goal(const std::vector<std::shared_ptr<Action>>& actions) : mActions{ actions }
	{
	}
}
