#include "clipboard.h"
#include <Windows.h>

BOOL write_clipboard_data(FILE* file)
{
	BOOL success = FALSE;

	if (!OpenClipboard(NULL))
		goto out;

	HANDLE handle = GetClipboardData(CF_UNICODETEXT);

	if (!handle)
		goto close;

	const LPVOID data = GlobalLock(handle);

	if (!data)
		goto close;

	success = TRUE;

	fwprintf(file, (LPCWSTR)data);
	GlobalUnlock(handle);
close:
	CloseClipboard();
out:
	return success;
}
