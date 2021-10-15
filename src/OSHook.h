#ifndef OSHOOK_OSHOOK_H
#define OSHOOK_OSHOOK_H


#include <Windows.h>
#include <memory>

#include "detours/manager/CDetourManager.h"
#include "detours/gl/DetourSwapBuffers.h"

#include "imgui/ImGuiManager.h"

namespace oshook {
    class OSHook {
    public:
        static std::shared_ptr<OSHook> g_oshook;

        void Init();

        void Destroy();

        std::shared_ptr<detours::CDetourManager> DetourManager() {
            return m_DetourManager;
        }

        std::shared_ptr<imgui::ImGuiManager> ImGuiManager() {
            return m_ImGuiManager;
        }
    private:
        std::shared_ptr<detours::CDetourManager> m_DetourManager;
        std::shared_ptr<imgui::ImGuiManager> m_ImGuiManager;

        void RegisterDetours();
    };
}


#endif //OSHOOK_OSHOOK_H
