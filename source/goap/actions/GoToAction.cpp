#include "pch.h"
#include "GoToAction.h"

namespace NAI
{
	namespace Goap
	{
		GoToAction::GoToAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			glm::vec3 destination) :
			BaseAction(preConditions, postConditions, 0),
			mDestination{ destination }
		{
		}
	}
}
