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

	WCHAR exe_path[MAX_PATH];
	const DWORD written = GetModuleFileName(NULL, exe_path, MAX_PATH);

	if (!written) {
		rc = GetLastError();
		goto close;
	}

	rc = RegSetValueEx(hkey, NULL, 0, REG_SZ, (BYTE*)exe_path,
			   (written + 1) * sizeof(WCHAR));
close:
	RegCloseKey(hkey);
out:
	return rc;
}
