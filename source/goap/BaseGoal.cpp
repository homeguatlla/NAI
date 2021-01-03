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
				std::vector<std::shared_ptr<IAction>> actions;

				actions.swap(mActions);

				int lastPredicatesSize = predicates.size();
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
							mActions.push_back(action);
							it = actions.erase(it);
						}
						else
						{
							++it;
						}
					}
				} while (static_cast<int>(predicates.size()) > lastPredicatesSize);

				satisfied = actions.empty() && !mActions.empty();
			}

			return satisfied;
		}

		void BaseGoal::Accomplished(std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			DoAccomplished(predicates);
		}

		void BaseGoal::Cancel()
		{
			if(HasActions())
			{
				mActions[mCurrentActionIndex]->Cancel();
			}

			mCurrentActionIndex = 0;
			
			DoCancel();
		}

		void BaseGoal::Reset()
		{
			mActions.clear();
			mCurrentActionIndex = 0;

			DoReset();
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
					if (!accomplishedPredicates.empty())
					{
						result = Utils::Concat(result, accomplishedPredicates);
						inputPredicates = Utils::Concat(inputPredicates, action->GetPostconditions());
					}
				}
			}

			return result;
		}

		void BaseGoal::AddStimulusAcceptance(const std::string& stimulusClassName, std::function<std::shared_ptr<IPredicate>()> creator)
		{
			auto found = mStimulusAccepted.find(stimulusClassName) != mStimulusAccepted.end();
			if(!found)
			{
				mStimulusAccepted[stimulusClassName] = creator;
			}
		}

		bool BaseGoal::IsStimulusAccepted(std::shared_ptr<IStimulus> stimulus) const
		{
			return mStimulusAccepted.find(stimulus->GetClassName()) != mStimulusAccepted.end();
		}

		std::shared_ptr<IPredicate> BaseGoal::TransformStimulusIntoPredicates(std::shared_ptr<IStimulus> stimulus) const
		{
			std::shared_ptr<IPredicate> predicate = nullptr;
			
			auto it = mStimulusAccepted.find(stimulus->GetClassName());
			const auto found =  it!= mStimulusAccepted.end();
			if(found)
			{
				predicate = it->second();
			}
			
			return predicate;
		}
	}
}
