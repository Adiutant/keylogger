#include "registry.h"
#include "constants.h"
#include <Windows.h>

void registry::add_to_startup() noexcept
{
    HKEY hkey;

    if (!RegCreateKeyExW(HKEY_CURRENT_USER, LP_SUB_KEY, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL))
    {
        WCHAR executable_path[MAX_PATH];
        GetModuleFileNameW(NULL, executable_path, MAX_PATH);

        RegSetValueExW(hkey, NULL, 0, REG_SZ, reinterpret_cast<BYTE*>(executable_path), MAX_PATH);
        RegCloseKey(hkey);
    }
}
