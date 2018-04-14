#pragma once

#include "win32.h"

struct library {
	const HMODULE module;
	LPVOID *const function;
	const LPCSTR name;
};
