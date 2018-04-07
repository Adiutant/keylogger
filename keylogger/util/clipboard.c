#include "clipboard.h"
#include <stdio.h>
#include <Windows.h>

// Writes the current clipboard data to the provided file.
BOOL write_clipboard_data(FILE* file) {
	BOOL success = FALSE;

	if (!OpenClipboard(NULL))
		goto out;

	HANDLE handle = GetClipboardData(CF_UNICODETEXT);

	if (!handle)
		goto close;

	const LPVOID data = GlobalLock(handle);

	if (!data)
		goto close;

	if (fwprintf(file, (WCHAR*)data) < 0)
		goto unlock;

	success = TRUE;
unlock:
	GlobalUnlock(handle);
close:
	CloseClipboard();
out:
	return success;
}
