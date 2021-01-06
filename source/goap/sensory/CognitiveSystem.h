#pragma once
#include <goap/memory/Memory.h>
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
                Memory<IStimulus>& memory, 
                std::shared_ptr<IAgent> agent);
        };
    }
}
