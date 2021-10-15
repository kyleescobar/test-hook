#include "dllmain.h"

bool APIENTRY DllMain( HMODULE hModule,
                       DWORD ul_reason_for_call,
                       LPVOID lpReserved )
{
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:

            AllocConsole();
            freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);

            oshook::OSHook::g_oshook = std::make_shared<oshook::OSHook>();
            oshook::OSHook::g_oshook->Init();

            break;
        case DLL_PROCESS_DETACH:

            oshook::OSHook::g_oshook->Destroy();
            oshook::OSHook::g_oshook.reset();

            break;
    }
    return true;
}
