#ifndef OSHOOK_DETOURS_MANAGER_CDETOUR_H
#define OSHOOK_DETOURS_MANAGER_CDETOUR_H

#include <windows.h>
#include <detours.h>
#include <cstdio>
#include <cstdint>

namespace oshook::detours {
    class CDetour {
    public:
        virtual void Apply() = 0;

        virtual void Remove() = 0;
    };
}


#endif //OSHOOK_DETOURS_MANAGER_CDETOUR_H
