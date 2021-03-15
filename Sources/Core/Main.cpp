/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Main
*/

#include "Core.hpp"
#include "UnknownExceptions.hpp"
#include "CheckFile.hpp"

int main(void)
{
    std::unique_ptr<Core> _Core(new Core());
    std::unique_ptr<CheckFile> _CheckFile(new CheckFile);
    try {
        _CheckFile->check("./Assets/Assets.txt");
        _Core->start();
        _Core->splashScreenScene();
        return (_Core->getExitStatus());
    } catch (Exceptions &error) {
        error.printError();
        return (_Core->getExitStatus());
    } catch (...) {
        UnknownExceptions::getUnknownExceptions();
        return (Constants::ERROR);
    }
    return (Constants::SUCCESS);
}
