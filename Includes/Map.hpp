/*
** EPITECH PROJECT, 2020
** Map
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "IGames.hpp"

class Map {
public:
    Map();
    ~Map();
    void setBasicMap();
    void generateRandomBlocks();
    void displayMap();
    int moveCheck(int, int);
    void modifyMap(int, int, int);
    void saveMap(std::ofstream &);
    void loadMap(std::ifstream &);
    std::vector<std::vector<int>> &getMap();

private:
    std::vector<std::vector<int>> _map;
};

#endif /* !MAP_HPP_ */
