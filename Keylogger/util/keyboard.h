#pragma once

#include <stddef.h>
#include <Windows.h>

BOOL set_keyboard_hook();

void get_keyboard_state(BYTE* buff, size_t size);

BOOL is_key_down(DWORD vk_code);

int kbd_to_unicode(const KBDLLHOOKSTRUCT* kbd_hook, LPWSTR buff, size_t size);
