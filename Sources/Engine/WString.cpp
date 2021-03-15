/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** WString
*/

#include "WString.hpp"

namespace Wrapper {
    const wchar_t *convertString(std::string &content)
    {
        std::wstring w_content = std::wstring(content.begin(), content.end());

        return (w_content.c_str());
    }

    const wchar_t *convertString(char *content)
    {
        std::string s_content = content;
        std::wstring w_content =
            std::wstring(s_content.begin(), s_content.end());

        return (w_content.c_str());
    }

    std::string convertString(const wchar_t *content)
    {
        std::wstring w_string(content);
        std::string s_string(w_string.begin(), w_string.end());

        return (s_string);
    }
}; // namespace Wrapper
