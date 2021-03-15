/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Exceptions
*/

#include "Exceptions.hpp"

Exceptions::Exceptions(const std::string &message)
{
    this->_message = message;
}

const char *Exceptions::what() const noexcept
{
    return (this->_message.data());
}

void Exceptions::printError() const
{
    std::cerr << this->_message << std::endl;
}
