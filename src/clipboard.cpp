#include "clipboard.hpp"
#include <Windows.h>

// Get the current clipboard data.
std::wstring clipboard::get_data()
{
    std::wstring clipboard_data;

    if (OpenClipboard(nullptr))
    {
        if (auto handle = GetClipboardData(CF_UNICODETEXT))
        {
            if (const auto data = GlobalLock(handle))
            {
                clipboard_data = static_cast<WCHAR*>(data);

                GlobalUnlock(handle);
            }
        }

        CloseClipboard();
    }

    return clipboard_data;
}
