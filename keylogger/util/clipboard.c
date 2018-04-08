#include "clipboard.h"

BOOL write_clipboard_data(FILE* const file)
{
	BOOL success = FALSE;

	if (!OpenClipboard(NULL))
		goto out;

	const HANDLE handle = GetClipboardData(CF_UNICODETEXT);

	if (!handle)
		goto close;

	const LPVOID data = GlobalLock(handle);

	if (!data)
		goto close;

	success = TRUE;

	fwprintf_s(file, (LPCWSTR)data);
	GlobalUnlock(handle);
close:
	CloseClipboard();
out:
	return success;
}
