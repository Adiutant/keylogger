#pragma once

#include "win32.h"

// TODO: docs
DWORD open_utf16_file(HANDLE *const file, const LPCWSTR name);

DWORD ensure_utf16(const HANDLE file);

DWORD write_wstr(const HANDLE file, const LPCWSTR content);
