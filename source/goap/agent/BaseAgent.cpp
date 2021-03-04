#include "pch.h"
#include "BaseAgent.h"
#include "goap/IPredicate.h"
#include "goap/predicates/PlaceIamPredicate.h"
#include "goap/IGoal.h"
#include <cassert>

#include "fsm/states/Processing.h"
#include "fsm/states/Planning.h"
#include "fsm/transitions/EnterPlanning.h"
#include "fsm/transitions/EnterProcessing.h"

namespace NAI
{
	namespace Goap
	{
		BaseAgent::BaseAgent(std::shared_ptr<IGoapPlanner> goapPlanner,
			const std::vector<std::shared_ptr<IGoal>>& goals,
			const std::vector<std::shared_ptr<IPredicate>>& predicates) :
			BaseAgent(goapPlanner, goals, predicates, nullptr)
		{
		}

		BaseAgent::BaseAgent(std::shared_ptr<IGoapPlanner> goapPlanner, 
		                     const std::vector<std::shared_ptr<IGoal>>& goals, 
		                     const std::vector<std::shared_ptr<IPredicate>>& predicates,
		                     const std::shared_ptr<PerceptionSystem> perceptionSystem) :
			mGoapPlanner{ goapPlanner },
			mGoals { goals },
			mPerceptionSystem{perceptionSystem},
			mIsAgentStartedUp{false}
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
			mIsAgentStartedUp = true;
		}

		void BaseAgent::Update(float elapsedTime)
		{
			if(mPerceptionSystem && mStatesMachine->GetCurrentState())
			{
				mPerceptionSystem->Update(elapsedTime, shared_from_this());
			}
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
			mPredicatesHandler.AddOrReplace(predicate);	
			mAgentContext->SetPredicatesHandler(mPredicatesHandler);
			NotifyPredicatesListChangedToProcessState();
		}

		void BaseAgent::OnUpdatePredicate(std::shared_ptr<IPredicate> predicate)
		{
			mPredicatesHandler.AddOrReplace(predicate);	
			mAgentContext->SetPredicatesHandler(mPredicatesHandler);
		}

		void BaseAgent::RemovePredicate(int id)
		{
			mPredicatesHandler.Remove(id);
		}

		const std::vector<std::shared_ptr<IPredicate>> BaseAgent::TransformStimulusIntoPredicates(const ShortTermMemory<IStimulus>& memory) const
		{
			std::vector<std::shared_ptr<IPredicate>> predicates;
			
			for(auto&& goal : mGoals)
			{			
				const auto predicate = goal->TransformStimulusIntoPredicates(memory);
			
				if(predicate != nullptr)
				{
					predicates.push_back(predicate);
				}
			}

			return predicates;
		}

		void BaseAgent::NotifyPredicatesListChangedToProcessState()
		{
			auto currentState = mStatesMachine->GetCurrentState();
			if (currentState != nullptr && currentState->GetID() == AgentState::STATE_PROCESSING)
			{
				auto processingState = std::static_pointer_cast<Processing>(currentState);
				processingState->OnPredicatesListChanged();
			}
		}

		AgentState BaseAgent::GetCurrentState() const
		{
			return mStatesMachine->GetCurrentState()->GetID();
		}

		void BaseAgent::AddSensoryThreshold(const std::string& stimulusClassName, std::shared_ptr<IThreshold> threshold)
		{
			const auto found = mThresholds.find(stimulusClassName) != mThresholds.end();
			if(!found)
			{
				mThresholds[stimulusClassName] = threshold;
			}
		}

		void BaseAgent::AddNewGoal(std::shared_ptr<IGoal> goal)
		{
			mGoals.push_back(goal);
			mAgentContext->SetGoals(mGoals);
			
			if(mIsAgentStartedUp)
			{
				goal->Create(shared_from_this());
			}
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
