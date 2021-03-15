/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** CheckFile
*/

#include "CheckFile.hpp"
#include <string>

void CheckFile::check(const std::string &path)
{
    std::ifstream file(path);
    std::string line;

    if (!file.good())
        throw Exceptions(Constants::File::ERROR_NO_ASSETS_FILE);
    while (std::getline(file, line)) {
        if (!std::filesystem::exists(line)) {
            std::cerr << line << Constants::File::FILE_DOESNT_EXISTS << std::endl;
            throw Exceptions(Constants::File::EXCEPTION);
        } else {
            std::cout << line << Constants::File::FILE_EXISTS << std::endl;
        }
    }
}
