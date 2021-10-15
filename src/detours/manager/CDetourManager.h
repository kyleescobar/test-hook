#ifndef OSHOOK_DETOURS_MANAGER_CDETOURMANAGER_H
#define OSHOOK_DETOURS_MANAGER_CDETOURMANAGER_H

#include <memory>
#include <vector>
#include "CDetour.h"

namespace oshook::detours {
    class CDetourManager {
    public:
        void RegisterDetour(const std::shared_ptr<CDetour> &detour);

        void ApplyDetours();

        void RemoveDetours();

    private:
        std::vector<std::shared_ptr<CDetour>> m_Detours;
    };
}


#endif //OSHOOK_DETOURS_MANAGER_CDETOURMANAGER_H
