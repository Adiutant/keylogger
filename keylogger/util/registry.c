#include "constants.h"
#include "registry.h"

LONG add_to_startup()
{
	HKEY hkey;
	LONG rc = RegCreateKeyEx(HKEY_CURRENT_USER, LP_SUB_KEY, 0, NULL,
				 REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
				 &hkey, NULL);

	if (rc)
		goto out;

	WCHAR executable_path[MAX_PATH];
	DWORD written = GetModuleFileName(NULL, executable_path, MAX_PATH);

	if (!written) {
		rc = GetLastError();
		goto close;
	}

	rc = RegSetValueEx(hkey, NULL, 0, REG_SZ, (BYTE*)executable_path,
			   written);
close:
	RegCloseKey(hkey);
out:
	return rc;
}
