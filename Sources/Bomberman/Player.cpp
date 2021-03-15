/*
** EPITECH PROJECT, 2020
** Player
** File description:
** Player
*/

#include "Player.hpp"
#include <string>

Player::Player()
{
    _pos = std::make_pair(1, 1);
    _bomb = 1;
    _speed = 1;
    _power = 1;
    _pass = false;
    _dead = false;
}

Player::~Player()
{
}

void Player::modifyDead()
{
    _dead = true;
}

bool Player::getDead() const
{
    return _dead;
}

std::vector<std::string> Player::split(const std::string &s, char seperator)
{
    std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;

    while ((pos = s.find(seperator, pos)) != std::string::npos) {
        std::string substring(s.substr(prev_pos, pos - prev_pos));
        output.push_back(substring);
        prev_pos = ++pos;
    }
    output.push_back(s.substr(prev_pos, pos - prev_pos));
    return output;
}

void Player::loadInfos(std::ifstream &file)
{
    std::string line;
    std::getline(file, line);
    std::vector<std::string> tab = split(line, ';');
    _bomb = std::stoi(tab[0]);
    _speed = std::stoi(tab[1]);
    _power = std::stoi(tab[2]);
    _pos = std::make_pair(std::stoi(tab[3]), std::stoi(tab[4]));
    _pass = std::stoi(tab[5]);
    while (std::getline(file, line)) {
        if (line == "Dangers")
            break;
        tab = split(line, ';');
        addBomb(std::stoi(tab[0]), std::stoi(tab[1]));
    }
    line.clear();
}

std::pair<int, int> Player::getPos() const
{
    return _pos;
}

void Player::move(int x, int y)
{
    _pos.first = x;
    _pos.second = y;
}

void Player::saveInfos(std::ofstream &file)
{
    file << _bomb << ";" << _speed << ";" << _power << ";" << _pos.first << ";"
         << _pos.second << ";";
    if (_pass == true)
        file << 1;
    else {
        file << 0;
    }
    file << std::endl;
    for (size_t i = 0; i < _bombs.size(); i++) {
        _bombs[i]->saveBomb(file);
    }
}

void Player::addBomb(int x, int y)
{
    _bombs.push_back(std::make_unique<Bomb>(x, y));
}

int Player::getBombs() const
{
    return (_bombs.size());
}

std::pair<int, int> Player::getBombPos(int bomb) const
{
    return _bombs[bomb]->getPos();
}

float Player::getBombSecond(int bomb) const
{
    return _bombs[bomb]->getSecond();
}

int Player::getMax() const
{
    return _bomb;
}

bool Player::getWallPass()
{
    return _pass;
}

void Player::removeBomb(int bomb)
{
    _bombs.erase(_bombs.begin() + bomb);
}

int Player::getPower() const
{
    return _power;
}

void Player::upBomb()
{
    _bomb += 1;
}

void Player::upPower()
{
    _power += 1;
}

void Player::upSpeed()
{
    _speed += 1;
}

void Player::wallPass()
{
    _pass = true;
}
