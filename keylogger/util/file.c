#include "file.h"

// TODO: VS always little endian?
#if REG_DWORD == REG_DWORD_LITTLE_ENDIAN
static const BYTE UTF16_MAGIC[] = { 0xFF, 0xFE };
#else
static const BYTE UTF16_MAGIC[] = { 0xFE, 0xFF };
#endif // REG_DWORD = REG_DWORD_LITTLE_ENDIAN

enum { MAGIC_SIZE = ARRAYSIZE(UTF16_MAGIC) };

DWORD open_utf16_file(HANDLE *const file, const LPCWSTR name)
{
	DWORD rc;
	HANDLE handle = CreateFile(
		name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		rc = GetLastError();
		goto out;
	}

	rc = ensure_utf16(handle);
out:
	*file = rc ? NULL : handle;
	return rc;
}

DWORD ensure_utf16(const HANDLE file)
{
	UCHAR buff[MAGIC_SIZE];
	DWORD read;
	BOOL success = LpReadFile(file, buff, MAGIC_SIZE, &read, NULL);

	if (!success)
		return GetLastError();

	if (!memcmp(buff, UTF16_MAGIC, MAGIC_SIZE))
		return 0;

	LARGE_INTEGER dist = { 0 };
	DWORD res = SetFilePointerEx(file, dist, NULL, FILE_BEGIN);

	if (res == INVALID_SET_FILE_POINTER)
		return GetLastError();

	DWORD count;
	success = WriteFile(file, UTF16_MAGIC, MAGIC_SIZE, &count, NULL);

	if (!success)
		return GetLastError();
	else if (count != MAGIC_SIZE)
		return 1;

	return 0;
}

DWORD write_wstr(const HANDLE file, const LPCWSTR content)
{
	DWORD buff_size = wcslen(content) * sizeof(content[0]);
	DWORD count;
	BOOL success = WriteFile(file, content, buff_size, &count, NULL);

	if (count != buff_size)
		return 1;

	return success ? 0 : GetLastError();
}
