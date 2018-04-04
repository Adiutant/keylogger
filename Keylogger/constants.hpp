#pragma once

#include <cstdint>
#include <Windows.h>

namespace constants {
	constexpr const DWORD vk_v{ 0x056 };
	constexpr const std::uint8_t key_buffer_size{ 4 };
	constexpr const std::uint16_t keyboard_state_size{ 256 };
	constexpr const LPCWSTR lp_sub_key{ L"Software\\Microsoft\\Windows\\CurrentVersion\\Run" };
}
