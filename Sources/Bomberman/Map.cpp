/*
** EPITECH PROJECT, 1020
** Map
** File description:
** Map
*/

#include "Map.hpp"
#include <string>

Map::Map()
{
    setBasicMap();
    generateRandomBlocks();
}

Map::~Map()
{
}

void Map::loadMap(std::ifstream &file)
{
    std::string line;
    int i = 0;

    std::getline(file, line);
    while (line != "Emap") {
        for (size_t j = 0; j < line.size(); j++) {
            _map[i][j] = (int)line[j] - 48;
        }
        i++;
        std::getline(file, line);
    }
    line.clear();
}

void Map::saveMap(std::ofstream &file)
{
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            file << _map[i][j];
        }
        file << std::endl;
    }
    file << "Emap" << std::endl;
}

void Map::generateRandomBlocks()
{
    std::srand(std::time(nullptr));

    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == 2 && (!(std::rand() % 3))) {
                _map[i][j] = 0;
            }
        }
    }
}

void Map::displayMap()
{
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            std::cout << _map[i][j];
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> &Map::getMap()
{
    return _map;
}

void Map::modifyMap(int x, int y, int objet)
{
    _map[x][y] = objet;
}

int Map::moveCheck(int x, int y)
{
    return _map[x][y];
}

void Map::setBasicMap()
{
    _map = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1},
            {1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1},
            {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
            {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
            {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
            {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
            {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
            {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
            {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
            {1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1},
            {1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
}
