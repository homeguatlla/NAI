#include "pch.h"
#include "BaseAction.h"
#include "IPredicate.h"
#include <algorithm>

namespace NAI
{
	namespace Goap
	{
		BaseAction::BaseAction(
			const std::vector<std::string>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			unsigned int cost) :
			mPreConditions{ preConditions },
			mPostConditions{ postConditions },
			mCost{ cost },
			mHasAccomplished { true },
			mHasCancelled { false }
		{
		}

		void BaseAction::Process(float elapsedTime)
		{
			DoProcess(elapsedTime);
		}

		bool BaseAction::SatisfyPrecondition(const std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			ResetMatchedPreConditions();
			mMatchedPreConditions = SatisfyConditions(mPreConditions, predicates);

			return mMatchedPreConditions.size() == mPreConditions.size();
		}

		bool BaseAction::SatisfyPostcondition(const std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			const auto result = SatisfyConditions(mPostConditions, predicates);

			return result.size() == mPostConditions.size() && result.size() > 0;
		}

		std::vector<std::shared_ptr<IPredicate>> BaseAction::GetPredicatesSatisfyPostconditions(const std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			return SatisfyConditions(mPostConditions, predicates);
		}

		std::vector<std::shared_ptr<IPredicate>> BaseAction::GetPredicatesSatisfyPreconditions(const std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			return SatisfyConditions(mPreConditions, predicates);
		}

		std::vector<std::shared_ptr<IPredicate>> BaseAction::SatisfyConditions(
        const std::vector<std::string>& conditions, 
        const std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			std::vector<std::shared_ptr<IPredicate>> result;

			std::all_of(conditions.begin(), conditions.end(),
                [&result, &predicates](const std::string& predicateA)
                {
                    const auto it = std::find_if(predicates.begin(), predicates.end(),
                        [predicateA](const std::shared_ptr<IPredicate>& predicateB)
                        {
                            return predicateA == predicateB->GetText();
                        });

                    const auto satisfy = it != predicates.end();
                    if (satisfy)
                    {
                        result.push_back(*it);
                    }

                    return satisfy;
                });

			return result;
		}

		std::vector<std::shared_ptr<IPredicate>> BaseAction::SatisfyConditions(
		const std::vector<std::shared_ptr<IPredicate>>& conditions, 
		const std::vector<std::shared_ptr<IPredicate>>& predicates)
		{
			std::vector<std::shared_ptr<IPredicate>> result;

			std::all_of(conditions.begin(), conditions.end(),
				[&result, &predicates](const std::shared_ptr<IPredicate>& predicateA)
				{
					const auto it = std::find_if(predicates.begin(), predicates.end(),
						[predicateA](const std::shared_ptr<IPredicate>& predicateB)
						{
							return predicateA->IsEqualTo(predicateB);
						});

					const auto satisfy = it != predicates.end();
					if (satisfy)
					{
						result.push_back(*it);
					}

					return satisfy;
				});

			return result;
		}

		void BaseAction::ResetMatchedPreConditions()
		{
			mMatchedPreConditions.clear();
		}

		void BaseAction::Cancel()
		{
			mHasCancelled = true;
		}

		const std::shared_ptr<IPredicate> BaseAction::GetPredicateMatchedPreconditionWithText(
			const std::string& text) const
		{
			auto it = std::find_if(mMatchedPreConditions.begin(), mMatchedPreConditions.end(),
				[text](const std::shared_ptr<IPredicate>& predicate)
				{
					return predicate->GetText() == text;
				});

			if(it != mMatchedPreConditions.end())
			{
				return *it;
			}
			else
			{
				return nullptr;
			}
		}
	}
}
