/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** UnknownExceptions
*/

#include <iostream>
#include <memory>

namespace UnknownExceptions {
    void getUnknownExceptions()
    {
        auto expPtr = std::current_exception();

        try {
            if (expPtr)
                std::rethrow_exception(expPtr);
        } catch (const std::exception &e) {
            std::cout << e.what();
        }
    }
} // namespace UnknownExceptions
