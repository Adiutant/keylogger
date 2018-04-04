#include "clipboard.hpp"
#include <Windows.h>

// Get the current clipboard data.
std::optional<std::wstring> clipboard_util::get_data() {
	const auto success = OpenClipboard(nullptr);

	if (!success)
		return std::nullopt;

	auto handle = GetClipboardData(CF_UNICODETEXT);

	if (!handle)
		return std::nullopt;

	const auto data = GlobalLock(handle);

	if (!data)
		return std::nullopt;

	std::wstring clipboard_data = static_cast<WCHAR*>(data);

	GlobalUnlock(handle);
	CloseClipboard();

	return clipboard_data;
}
