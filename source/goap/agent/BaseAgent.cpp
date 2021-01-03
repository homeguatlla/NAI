#include "pch.h"
#include "BaseAgent.h"
#include "goap/IPredicate.h"
#include "goap/predicates/PlaceIamPredicate.h"
#include "goap/IGoal.h"

#include <cassert>

#include "fsm/states/Processing.h"
#include "fsm/transitions/EnterPlanning.h"
#include "fsm/transitions/EnterProcessing.h"

namespace NAI
{
	namespace Goap
	{
		BaseAgent::BaseAgent(std::shared_ptr<IGoapPlanner> goapPlanner, 
			std::vector<std::shared_ptr<IGoal>>& goals, 
			std::vector<std::shared_ptr<IPredicate>>& predicates) :
			mGoapPlanner{ goapPlanner },
			mGoals { goals }
		{
			assert(goapPlanner);
			mPredicatesHandler.Reset(predicates);
			CreateStatesMachine();
		}

		void BaseAgent::StartUp()
		{
			for (auto&& goal : mGoals)
			{
				goal->Create(shared_from_this());
			}
		}

		void BaseAgent::Update(float elapsedTime)
		{
			mStatesMachine->Update(elapsedTime);
			mPredicatesHandler = mAgentContext->GetPredicatesHandler();
		}

		bool BaseAgent::HasPredicate(int predicateID) const
		{
			const auto predicateFound = mPredicatesHandler.FindById(predicateID);
			
			return predicateFound != nullptr;
		}

		std::string BaseAgent::WhereIam() const
		{
			const auto predicateFound = mPredicatesHandler.FindByText(std::string("PlaceIam"));
			
			if (predicateFound != nullptr)
			{
				const auto placeIamPredicate = std::static_pointer_cast<PlaceIamPredicate>(predicateFound);
				return placeIamPredicate->GetPlaceName();
			}
			else
			{
				return "";
			}
		}

		void BaseAgent::OnNewPredicate(std::shared_ptr<IPredicate> predicate)
		{
			if (!HasPredicate(predicate->GetID()))
			{
				mPredicatesHandler.Add(predicate);
				mAgentContext->SetPredicatesHandler(mPredicatesHandler);
				NotifyPredicatesListChangedToProcessState();
			}
		}


		bool BaseAgent::IsStimulusAccepted(std::shared_ptr<IStimulus> stimulus) const
		{
			for(auto&& goal : mGoals)
			{
				if(goal->IsStimulusAccepted(stimulus))
				{
					return true;
				}
			}
			
			return false;
		}

		const std::vector<std::shared_ptr<IPredicate>> BaseAgent::TransformStimulusIntoPredicates(std::shared_ptr<IStimulus> stimulus) const
		{
			std::vector<std::shared_ptr<IPredicate>> predicates;
			
			for(auto&& goal : mGoals)
			{
				if(goal->IsStimulusAccepted(stimulus))
				{
					const auto predicate = goal->TransformStimulusIntoPredicates(stimulus);
				
					if(predicate != nullptr)
					{
						predicates.push_back(predicate);
					}
				}
			}

			return predicates;
		}

		void BaseAgent::NotifyPredicatesListChangedToProcessState()
		{
			auto currentState = mStatesMachine->GetCurrentState();
			if (currentState->GetID() == AgentState::STATE_PROCESSING)
			{
				auto processingState = std::static_pointer_cast<Processing>(currentState);
				processingState->OnPredicatesListChanged();
			}
		}

		AgentState BaseAgent::GetCurrentState() const
		{
			return mStatesMachine->GetCurrentState()->GetID();
		}

		void BaseAgent::CreateStatesMachine()
		{
			mAgentContext = std::make_shared<AgentContext>(mGoapPlanner, mPredicatesHandler, mGoals);
			mStatesMachine = std::make_unique<core::utils::FSM::StatesMachine<AgentState, AgentContext>>(mAgentContext);

			auto planning = std::make_shared<Planning>();
			auto processing = std::make_shared<Processing>();

			mStatesMachine->AddState(planning);
			mStatesMachine->AddState(processing);

			//from Planning
			mStatesMachine->AddTransition(std::make_unique<EnterProcessing>(planning, processing));

			//from Processing
			mStatesMachine->AddTransition(std::make_unique<EnterPlanning>(processing, planning));

			mStatesMachine->SetInitialState(planning->GetID());
		}
	}
}
