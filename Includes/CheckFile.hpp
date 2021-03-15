/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** CheckFile
*/

#ifndef CHECKFILE_HPP_
#define CHECKFILE_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Exceptions.hpp"
#include "Constants.hpp"

class CheckFile {
public:
    CheckFile() = default;
    ~CheckFile() = default;

    void check(const std::string &path);

private:
};

#endif
