#include <stdio.h>
#include <locale>
#include <codecvt>

const std::string ws2s(const std::wstring& src);

const std::wstring s2ws(const std::string& src);

const std::string ws2utf8(const std::wstring& src);

const std::wstring utf8_2_ws(const std::string& src);