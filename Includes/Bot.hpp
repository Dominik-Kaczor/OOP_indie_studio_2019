/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** BOT
*/

#ifndef BOT_HPP_
#define BOT_HPP_
#include <iostream>
#include <string>
#include "Bomb.hpp"

class Bot {
public:
    Bot();
    ~Bot();
    void move(int, int);
    std::pair<int, int> getPos() const;
    void setPos(int, int);
    void addBomb(int, int);
    int getBombs() const;
    int getMax() const;
    std::pair<int, int> getBombPos(int) const;
    float getBombSecond(int) const;
    void removeBomb(int);
    int getPower() const;
    void upPower();
    void upBomb();
    void upSpeed();
    void wallPass();
    void loadInfos(std::ifstream &file);
    void saveInfos(std::ofstream &file);
    std::vector<std::string> split(const std::string &s, char seperator);
    bool getWallPass();
    bool getAlive() const;
    void setAlive(bool);
    int getNbrBlock(std::vector<std::vector<int>>);
    bool checkHitPlayer(std::pair<int, int>);
    std::pair<int, int> getPlayerPos(std::vector<std::vector<int>>) const;
    void removeTopDest();
    void setGetNewDest(bool);
    bool getGetNewDest() const;
    std::vector<int> getDest() const;
    void setDest(std::vector<int>);
    void defenseDest(std::vector<std::vector<int>>,
                     std::vector<std::vector<int>>);
    void offenceDest(std::vector<std::vector<int>>);
    void newDest(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
    bool getDefense() const;

private:
    std::vector<std::unique_ptr<Bomb>> _bombs;
    std::pair<int, int> _pos;
    std::vector<int> _dest;
    int _bomb;
    int _speed;
    int _power;
    bool _pass;
    bool _alive;
    bool _getNewDest;
    bool _defense;
};

#endif /* !BOT_HPP_ */
