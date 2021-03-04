#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>

namespace NAI {
    namespace Navigation {
        class INavigationPath;
    }
}

namespace NAI
{
    namespace Goap
    {
        class IPredicate;
        
        class IGoToGoal
        {
        public:
            virtual ~IGoToGoal() = default;
            virtual void OnNavigationPath(const std::string& placeName, const std::shared_ptr<NAI::Navigation::INavigationPath>& path) = 0;
            virtual glm::vec3 GetDestination(const std::shared_ptr<NAI::Goap::IPredicate> predicate) const = 0;
        };
    }
}
