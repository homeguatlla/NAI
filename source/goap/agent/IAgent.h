#pragma once
#include "goap/GoapTypes.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include <map>

namespace NAI
{
	namespace Goap
	{
		class IPredicate;
		class IGoal;
		class IStimulus;
		class IThreshold;
		
		class IAgent
		{
		public:
			virtual ~IAgent() = default;

			virtual void StartUp() = 0;
			virtual void Update(float elapsedTime) = 0;
			virtual AgentState GetCurrentState() const = 0;
			virtual bool HasPredicate(int predicateID) const = 0;
			virtual std::string WhereIam() const = 0;
			virtual void OnNewPredicate(std::shared_ptr<IPredicate> predicate) = 0;
			virtual const std::vector<std::shared_ptr<IGoal>>& GetGoals() const = 0;
			virtual const std::vector<std::shared_ptr<IPredicate>>& GetPredicates() const = 0;
			virtual glm::vec3 GetPosition() const = 0;
			virtual void MoveTo(float elapsedTime, const glm::vec3& point) = 0;
			virtual bool IsStimulusAccepted(std::shared_ptr<IStimulus> stimulus) const = 0;
			virtual const std::vector<std::shared_ptr<IPredicate>> TransformStimulusIntoPredicates(std::shared_ptr<IStimulus> stimulus) const = 0;
			virtual void AddSensoryThreshold(const std::string& stimulusClassName, std::shared_ptr<IThreshold> threshold) = 0;
			virtual std::map<std::string, std::shared_ptr<IThreshold>> GetSensoryThresholds() const = 0; 
		};
	}
}

