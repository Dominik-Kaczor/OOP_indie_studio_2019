/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_
#include <iostream>

class Exceptions : public std::exception {
public:
    Exceptions(const std::string &);
    const char *what() const noexcept override;
    void printError() const;

private:
    std::string _message;
};

#endif /* !EXCEPTIONS_HPP_ */
