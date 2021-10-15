#include "DetourSwapBuffers.h"

namespace odg = oshook::detours::gl;
using namespace odg;

uint32_t odg::DetourSwapBuffers::m_SwapCount = 0;
SwapBuffers_Def odg::DetourSwapBuffers::m_OriginalFunction = nullptr;

void odg::DetourSwapBuffers::Apply() {
    m_OriginalFunction = &SwapBuffers;
    DetourAttach(&m_OriginalFunction, &HookedFunction);
    std::printf("Hooked SwapBuffers\n");
}

void odg::DetourSwapBuffers::Remove() {
    DetourDetach(&m_OriginalFunction, &HookedFunction);
    std::printf("Unhooked SwapBuffers\n");
}

BOOL odg::DetourSwapBuffers::HookedFunction(HDC hDeviceContext) {
    m_SwapCount++;
    oshook::OSHook::g_oshook->ImGuiManager()->FrameGL();
    BOOL result = m_OriginalFunction(hDeviceContext);
    oshook::OSHook::g_oshook->ImGuiManager()->PostSwapBuffers();
    return result;
}
