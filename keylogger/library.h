#pragma once

#include "win32.h"

typedef struct _LIBRARY {
	const HMODULE module;
	LPVOID *const function;
	const LPCSTR name;
} LIBRARY;