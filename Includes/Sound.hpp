/*
** EPITECH PROJECT, 2020
** indie
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_
#include <map>
#include <SFML/Audio.hpp>

class Sound {
public:
    Sound() = default;
    ~Sound() = default;
    void addSound(const std::string &path);
    void playSound();
    void stopSound();

protected:
private:
    sf::Music _sound;
};

#endif /* !SOUND_HPP_ */
