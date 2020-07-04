#include "pch.h"
#include "source/goap/predicates/GoapPredicates.h"

using namespace NAI::Goap;

std::shared_ptr<IPredicate> Predicates::PREDICATE_GO_TO = std::make_shared<GoToPredicate>("GoTo");
std::shared_ptr<IPredicate> Predicates::PREDICATE_GOT_PATH = std::make_shared<BasePredicate>("GotPath");
std::shared_ptr<IPredicate> Predicates::PREDICATE_AT_PLACE = std::make_shared<BasePredicate>("AtPlace");