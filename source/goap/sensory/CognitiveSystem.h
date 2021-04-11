#pragma once
#include <goap/memory/ShortTermMemory.h>
#include <memory>

namespace NAI
{
    namespace Goap
    {
        class IStimulus;
        class IAgent;

        class CognitiveSystem
        {
        public:
            CognitiveSystem() = default;
            ~CognitiveSystem() = default;

           void Update(
                float elapsedTime, 
                ShortTermMemory<IStimulus>& memory, 
                std::shared_ptr<IAgent> agent);

        private:
            void AddPredicatesFromStimulus(ShortTermMemory<IStimulus>& memory, std::shared_ptr<IAgent> agent);
            void RemovePredicatesFromStimulus(std::shared_ptr<IAgent> agent);
        };
    }
}
