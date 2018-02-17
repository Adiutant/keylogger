#include "clipboard.hpp"
#include <Windows.h>

// Get the current clipboard data.
std::wstring clipboard::get_data()
{
    if (OpenClipboard(nullptr))
    {
        if (auto handle = GetClipboardData(CF_UNICODETEXT))
        {
            if (const auto data = GlobalLock(handle))
            {
                const auto clipboard_data = std::wstring{ static_cast<WCHAR*>(data) };

                GlobalUnlock(handle);

                return clipboard_data;
            }
        }

        CloseClipboard();
    }

    return {};
}
