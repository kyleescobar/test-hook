#include "ImGuiManager.h"
#include "../detours/gl/DetourSwapBuffers.h"

using namespace oshook::imgui;

// static initializers
WNDPROC oshook::imgui::ImGuiManager::m_originalWndProc = nullptr;
bool oshook::imgui::ImGuiManager::m_initialized = false;

bool oshook::imgui::ImGuiManager::InitGL(HDC hDeviceContext) {
    HWND hWnd = WindowFromDC(hDeviceContext);

    m_originalWndProc = (WNDPROC) (SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR) &WndProc));

    if (!hWnd) {
        return false;
    }

    IMGUI_CHECKVERSION();
    glewInit();
    if (!ImGui::CreateContext()) {
        return false;
    }

    if (!ImGui_ImplWin32_Init(hWnd)) {
        ImGui::DestroyContext();
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init()) {
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        return false;
    }

    ImGui::StyleColorsDark();

    std::printf("ImGui GL Initialized\n");
    m_initialized = true;

    return true;
}

void oshook::imgui::ImGuiManager::FrameGL() {
    HDC deviceContext = wglGetCurrentDC();

    if (!m_initialized) {
        InitGL(deviceContext);
    } else {
        if (!m_ready) {
            return;
        }
        std::printf("\rDraw count: %d", oshook::detours::gl::DetourSwapBuffers::m_SwapCount);
        TryToggleMenu();

        if (m_menuOpen) {
            ImGui::ShowDemoWindow(&m_menuOpen);
        }

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_ready = false;
    }
}

void oshook::imgui::ImGuiManager::PostSwapBuffers() {
    // I don't want to know why, but this stupid overlay
    // won't display unless this NewFrame stuff is called
    // after SwapBuffers. Hopefully this doesn't make
    // the overlay lag behind the game by a frame.
    if (!m_initialized) {
        return;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    m_ready = true;
}

void oshook::imgui::ImGuiManager::TryToggleMenu() {
    if (ImGui::IsKeyPressed(VK_INSERT, false)) {
        std::printf("Toggling menu %d -> %d\n", m_menuOpen, !m_menuOpen);
        m_menuOpen = !m_menuOpen;
    }
}

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT oshook::imgui::ImGuiManager::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (!m_initialized) {
        return false;
    }

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
        return true;
    }

    ImGuiIO &io = ImGui::GetIO();
    if (io.WantCaptureKeyboard || io.WantCaptureMouse) {
        return true;
    }

    return CallWindowProc(m_originalWndProc, hWnd, msg, wParam, lParam);
}