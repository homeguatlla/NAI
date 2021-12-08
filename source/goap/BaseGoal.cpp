#include "pch.h"
#include "BaseGoal.h"
#include "IAction.h"
#include "GoapUtils.h"
#include <algorithm>

#include "sensory/IStimulus.h"

namespace NAI
{
	namespace Goap
	{
		BaseGoal::BaseGoal() :
			mCurrentActionIndex{ 0 },
			mCost{ 0 }
		{

		}

		BaseGoal::BaseGoal(const std::vector<std::shared_ptr<IAction>>& actions) : 
			mActions{ actions }, 
			mCurrentActionIndex { 0 } , 
			mCost{ 0 }
		{
			CalculateCost();
		}

		void BaseGoal::Create(std::shared_ptr<IAgent> agent)
		{
			DoCreate(agent);
		}

		void BaseGoal::CalculateCost()
		{
			for (auto&& action : mActions)
			{
				mCost += action->GetCost();
			}
		}

		std::shared_ptr<IAction> BaseGoal::GetNextAction()
		{
			return HasActions() ? mActions[mCurrentActionIndex++] : nullptr;
		}

		bool BaseGoal::SatisfyActions(const std::vector<std::shared_ptr<IPredicate>>& inputPredicates)
		{
			auto satisfied = false;

			if (!inputPredicates.empty() && !mActions.empty())
			{
				auto predicates = inputPredicates;
				std::vector<std::shared_ptr<IAction>> actions = mActions, actionsSatisfy;

				auto lastPredicatesSize = predicates.size();
				do
				{
					lastPredicatesSize = predicates.size();
					for (auto it = actions.begin(); it != actions.end();)
					{
						auto action = *it;
						if (action->SatisfyPostcondition(predicates))
						{
							it = actions.erase(it);
						}
						else if (action->SatisfyPrecondition(predicates))
						{
							const auto postconditions = action->GetPostconditions();
							predicates.insert(end(predicates), begin(postconditions), end(postconditions));
							actionsSatisfy.push_back(action);
							it = actions.erase(it);
						}
						else
						{
							++it;
						}
					}
				} while (static_cast<int>(predicates.size()) > lastPredicatesSize);

				satisfied = actions.empty() && !actionsSatisfy.empty();
			}

			return satisfied;
		}

		void BaseGoal::Accomplished(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			DoAccomplished(predicates);
		}

		void BaseGoal::Cancel(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			if(HasActions())
			{
				mActions[mCurrentActionIndex]->Cancel();
			}

			mCurrentActionIndex = 0;
			
			DoCancel(predicates);
		}

		void BaseGoal::Reset(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			mActions.clear();
			mCurrentActionIndex = 0;

			DoReset(predicates);
		}

		std::vector<std::shared_ptr<IPredicate>> BaseGoal::GetPredicatesCanBeAccomplished(
			std::vector<std::shared_ptr<IPredicate>> desiredPredicates)
		{
			std::vector<std::shared_ptr<IPredicate>> result;

			if(!desiredPredicates.empty())
			{
				for (auto&& action : mActions)
				{
					auto accomplishedPredicates = action->GetPredicatesSatisfyPostconditions(desiredPredicates);
					if (!accomplishedPredicates.empty())
					{
						result = Utils::Concat(result, accomplishedPredicates);
					}
				}
			}

			return result;
		}

		std::vector<std::shared_ptr<IPredicate>> BaseGoal::GetPredicatesSatisfyPreconditions(
			std::vector<std::shared_ptr<IPredicate>> inputPredicates)
		{
			std::vector<std::shared_ptr<IPredicate>> result;

			if (!inputPredicates.empty())
			{
				for (auto&& action : mActions)
				{
					auto accomplishedPredicates = action->GetPredicatesSatisfyPreconditions(inputPredicates);
					if (accomplishedPredicates.size() == action->GetPreconditions().size())
					{
						result = Utils::Concat(result, accomplishedPredicates);
						//esto no se puede hacer pues devolverá predicados nuevos que no estaban al inicio
						//si no quitamos los que se han añadido como postcondición.
						//De momento pues, este método solo devolverá aquellos predicados de la lista inicial
						//que se satisfacen alguna precondición
						//inputPredicates = Utils::Concat(inputPredicates, action->GetPostconditions());
					}
				}
			}

			//solo devuelve los predicados de la lista inicial que cumplen alguna precondición de alguna acción.
			//a partir de ahí, si se ha validado que se puede ejecutar el goal,
			//se supone que se podrá ejecutar esa acción y por tanto las demás.
			return result;
		}

		std::shared_ptr<IPredicate> BaseGoal::TransformStimulusIntoPredicates(const ShortTermMemory<IStimulus>& memory)
		{
			return DoTransformStimulusIntoPredicates(memory);
		}

		std::vector<int> BaseGoal::GetPredicatesIdsToRemove() const
		{
			return DoGetPredicatesIdsToRemove();	
		}
	}
}
