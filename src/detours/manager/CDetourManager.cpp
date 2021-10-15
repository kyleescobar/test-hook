#include <Windows.h>
#include "CDetourManager.h"
#include "detours.h"

using namespace oshook::detours;

void oshook::detours::CDetourManager::RegisterDetour(const std::shared_ptr<CDetour> &detour) {
    m_Detours.push_back(detour);
}

void oshook::detours::CDetourManager::ApplyDetours() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const std::shared_ptr<CDetour>& detour : m_Detours) {
        detour->Apply();
    }
    DetourTransactionCommit();
}

void oshook::detours::CDetourManager::RemoveDetours() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const std::shared_ptr<CDetour>& detour : m_Detours) {
        detour->Remove();
    }
    DetourTransactionCommit();
}
