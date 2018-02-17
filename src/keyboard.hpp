#pragma once

#include <Windows.h>
#include <string>

namespace keyboard
{
    void set_hook() noexcept;

    void get_state(BYTE* state) noexcept;

    bool is_down(DWORD vk_code) noexcept;

    std::wstring kbd_to_unicode(const KBDLLHOOKSTRUCT* kbd_hook) noexcept;
}
