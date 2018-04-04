#pragma once

#include <Windows.h>
#include <string>
#include <vector>

namespace keyboard_util {
	void set_hook() noexcept;

	std::vector<BYTE> get_state();

	bool is_down(DWORD vk_code) noexcept;

	// TODO: const ref
	std::wstring kbd_to_unicode(const KBDLLHOOKSTRUCT* kbd_hook);
}
