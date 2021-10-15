#ifndef OSHOOK_IMGUI_IMGUIMANAGER_H
#define OSHOOK_IMGUI_IMGUIMANAGER_H

#include <Windows.h>
#include <cstdio>
#include <GL/glew.h>

#include "../../third_party/imgui/imgui.h"
#include "../../third_party/imgui/imgui_internal.h"
#include "../../third_party/imgui/backends/imgui_impl_win32.h"
#include "../../third_party/imgui/backends/imgui_impl_opengl3.h"

namespace oshook::imgui {
    class ImGuiManager {
    public:
        bool InitGL(HDC hDeviceContext);

        void FrameGL();

        void PostSwapBuffers();

        static LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        static WNDPROC m_originalWndProc;

        static bool m_initialized;

        bool m_menuOpen = false;

        bool m_ready = false;

        void TryToggleMenu();
    };
}

#endif //OSHOOK_IMGUI_IMGUIMANAGER_H
