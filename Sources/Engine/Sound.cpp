/*
** EPITECH PROJECT, 2020
** indie
** File description:
** Sound
*/

#include "Sound.hpp"

void Sound::addSound(const std::string &path)
{
    this->_sound.openFromFile(path);
}

void Sound::playSound()
{
    this->_sound.play();
}

void Sound::stopSound()
{
    this->_sound.stop();
}
