/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** WString
*/

#ifndef WSTRING_HPP_
#define WSTRING_HPP_
#include <iostream>

namespace Wrapper {
    const wchar_t *convertString(std::string &);
    const wchar_t *convertString(char *);
    std::string convertString(const wchar_t *);
} // namespace Wrapper

#endif /* !WSTRING_HPP_ */
