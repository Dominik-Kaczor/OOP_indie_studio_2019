/*
** EPITECH PROJECT, 2020
** Bomb
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(int x, int y)
{
    _pos.first = x;
    _pos.second = y;
    _time = std::clock();
}

Bomb::~Bomb()
{
}

void Bomb::saveBomb(std::ofstream &file)
{
    file << _pos.first << ";" << _pos.second << std::endl;
}

std::pair<int, int> Bomb::getPos() const
{
    return _pos;
}

void Bomb::placing(int x, int y)
{
    _pos.first = x;
    _pos.second = y;
    _time = std::clock();
}

float Bomb::getSecond() const
{
    clock_t time_req;

    time_req = clock() - _time;
    return (static_cast<float>(time_req) / CLOCKS_PER_SEC);
}

void Bomb::reset()
{
    _pos.first = -1;
    _pos.second = -1;
}
