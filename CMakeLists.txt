cmake_minimum_required(VERSION 3.17)
project(oshook)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/libs/detour ${CMAKE_SOURCE_DIR}/libs/glew ${CMAKE_SOURCE_DIR}/third_party/imgui)
link_directories(${CMAKE_SOURCE_DIR}/libs/detour ${CMAKE_SOURCE_DIR}/libs/glew)

add_library(oshook SHARED
        src/detours/manager/CDetourManager.cpp
        src/detours/manager/CDetourManager.h
        src/detours/manager/CDetour.h
        src/dllmain.cpp
        src/dllmain.h
        src/OSHook.cpp
        src/OSHook.h
        src/imgui/ImGuiManager.cpp
        src/imgui/ImGuiManager.h
        src/detours/gl/DetourSwapBuffers.cpp
        src/detours/gl/DetourSwapBuffers.h
        third_party/imgui/backends/imgui_impl_opengl3.cpp
        third_party/imgui/backends/imgui_impl_opengl3.h
        third_party/imgui/backends/imgui_impl_win32.cpp
        third_party/imgui/backends/imgui_impl_win32.h
        third_party/imgui/imconfig.h
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui.h
        third_party/imgui/imgui_demo.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_internal.h
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/imstb_rectpack.h
        third_party/imgui/imstb_textedit.h
        third_party/imgui/imstb_truetype.h
        third_party/glew.c)

set_target_properties(oshook PROPERTIES COMPILE_FLAGS "/D_AMD64_ /D_WIN64 /W4 /DGLEW_STATIC")

target_include_directories(oshook PUBLIC libs/detour libs/glew)
target_link_libraries(oshook detours syelog opengl32)