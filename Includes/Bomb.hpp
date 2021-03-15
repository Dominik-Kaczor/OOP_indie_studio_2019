/*
** EPITECH PROJECT, 2020
** Bomb
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "IGames.hpp"

class Bomb {
public:
    Bomb(int x, int y);
    ~Bomb();
    void placing(int, int);
    float getSecond() const;
    void saveBomb(std::ofstream &file);
    void reset();
    std::pair<int, int> getPos() const;

private:
    std::pair<int, int> _pos;
    std::clock_t _time;
};

#endif /* !BOMB_HPP_ */
