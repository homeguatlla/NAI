#pragma once
#include "source/goap/BasePredicate.h"
#include <string>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		static std::shared_ptr<IPredicate> PREDICATE_GO_TO = std::make_shared<BasePredicate>("GoTo");
		static std::shared_ptr<IPredicate> PREDICATE_GOT_PATH = std::make_shared<BasePredicate>("GotPath");
		static std::shared_ptr<IPredicate> PREDICATE_AT_PLACE = std::make_shared<BasePredicate>("AtPlace");
	}
}

