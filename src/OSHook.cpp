#include "OSHook.h"

using namespace oshook;

std::shared_ptr<OSHook> oshook::OSHook::g_oshook = nullptr;

void oshook::OSHook::Init() {
    m_ImGuiManager = std::make_shared<imgui::ImGuiManager>();

    m_DetourManager = std::make_shared<detours::CDetourManager>();
    RegisterDetours();
    m_DetourManager->ApplyDetours();
}

void oshook::OSHook::Destroy() {
    m_DetourManager->RemoveDetours();
}

void oshook::OSHook::RegisterDetours() {
    m_DetourManager->RegisterDetour(std::make_shared<detours::gl::DetourSwapBuffers>());
}
