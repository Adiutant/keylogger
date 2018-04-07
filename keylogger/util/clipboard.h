#pragma once

#include <stdio.h>
#include <Windows.h>

/*
 * write_clipboard_data - Writes the current clipboard data to the provided
 * file.
 * @file: The file in which the clipboard data will be written.
 *
 * Returns a non-zero value if the function succeeds. If not, returns zero.
 */
BOOL write_clipboard_data(FILE* file);
