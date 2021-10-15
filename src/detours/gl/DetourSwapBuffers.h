#ifndef OSHOOK_DETOURS_GL_DETOURSWAPBUFFERS_H
#define OSHOOK_DETOURS_GL_DETOURSWAPBUFFERS_H

#include "../manager/CDetour.h"
#include "../../OSHook.h"

namespace oshook::detours::gl {
    using SwapBuffers_Def = BOOL(WINAPI *)(HDC);

    class DetourSwapBuffers : public CDetour {
    public:
        static uint32_t m_SwapCount;

        void Apply() override;

        void Remove() override;

        static BOOL HookedFunction(HDC hDeviceContext);
    private:
        static SwapBuffers_Def m_OriginalFunction;
    };
}


#endif //OSHOOK_DETOURS_GL_DETOURSWAPBUFFERS_H
