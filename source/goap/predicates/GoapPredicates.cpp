#include "pch.h"
#include "goap/predicates/GoapPredicates.h"
#include "goap/GoapTypes.h"

using namespace NAI::Goap;

std::shared_ptr<IPredicate> Predicates::PREDICATE_GO_TO = std::make_shared<GoToPredicate>(PREDICATE_GO_TO_ID, "GoTo");
std::shared_ptr<IPredicate> Predicates::PREDICATE_GOT_PATH = std::make_shared<BasePredicate>(PREDICATE_GOT_PATH_ID, "GotPath");