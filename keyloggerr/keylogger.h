#pragma once

#include <Windows.h>

BOOL is_ignored(DWORD vk_code);

LPCWSTR get_key_value(DWORD vk_code);

void log_kbd(const KBDLLHOOKSTRUCT* kbd_hook);
