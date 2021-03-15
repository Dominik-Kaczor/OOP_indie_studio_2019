/*
** EPITECH PROJECT, 2020
** Bot
** File description:
** Bot
*/

#include "Bot.hpp"

Bot::Bot()
{
    _bomb = 1;
    _speed = 1;
    _power = 1;
    _pass = false;
    _alive = true;
    _getNewDest = true;
    _dest = {};
    _defense = false;
}

Bot::~Bot()
{
}

std::vector<std::string> Bot::split(const std::string &s, char seperator)
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

void Bot::loadInfos(std::ifstream &file)
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

void Bot::saveInfos(std::ofstream &file)
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
    file << "Dangers" << std::endl;
}

void Bot::offenceDest(std::vector<std::vector<int>> map)
{
    std::pair<int, int> playerPos = getPlayerPos(map);
    int x = playerPos.first - _pos.first;
    int y = playerPos.second - _pos.second;
    bool first;
    int xBis = -1;
    int yBis = -1;
    int xGoal = _pos.first;
    int yGoal = _pos.second;

    if (x > 0)
        xBis = 1;
    if (y > 0)
        yBis = 1;
    if (abs(x) > abs(y)) {
        first = true;
    } else {
        first = false;
    }
    while (x != 0 && y != 0 &&
           (map[xGoal + xBis][yGoal] == 0 || map[xGoal][yGoal + yBis] == 0)) {
        if (!first && (map[xGoal][yGoal + yBis] == VOID ||
                       map[xGoal][yGoal + yBis] == SPEED ||
                       map[xGoal][yGoal + yBis] == WALLPASS ||
                       map[xGoal][yGoal + yBis] == POWER ||
                       map[xGoal][yGoal + yBis] == UPBOMB)) {
            yGoal = yGoal + yBis;
            y += yBis;
            if (yBis == 1)
                _dest.push_back(1);
            else
                _dest.push_back(3);
        } else if (map[xGoal + xBis][yGoal] == VOID ||
                   map[xGoal + xBis][yGoal] == SPEED ||
                   map[xGoal + xBis][yGoal] == WALLPASS ||
                   map[xGoal + xBis][yGoal] == POWER ||
                   map[xGoal + xBis][yGoal] == UPBOMB) {
            xGoal = xGoal + xBis;
            x += xBis;
            if (xBis == 1)
                _dest.push_back(2);
            else
                _dest.push_back(0);
        } else if (map[xGoal][yGoal + yBis] == VOID ||
                   map[xGoal][yGoal + yBis] == SPEED ||
                   map[xGoal][yGoal + yBis] == WALLPASS ||
                   map[xGoal][yGoal + yBis] == POWER ||
                   map[xGoal][yGoal + yBis] == UPBOMB) {
            y += yBis;
            yGoal = yGoal + yBis;
            if (yBis == 1)
                _dest.push_back(1);
            else
                _dest.push_back(3);
        } else {
            first = !first;
            int last = _dest[_dest.size() - 1];
            _dest.pop_back();
            if (last == 0 || last == 2) {
                xGoal = xGoal - xBis;
                x -= xBis;
            } else {
                y += yBis;
                yGoal = yGoal + yBis;
            }
        }
    }
}

std::vector<int> getMinToSafety(std::vector<int> hist, std::pair<int, int> pos,
                                std::vector<std::vector<int>> map,
                                std::vector<std::vector<int>> danger, int dir)
{
    if (dir == 0)
        pos.first -= 1;
    if (dir == 1)
        pos.second += 1;
    if (dir == 2)
        pos.first += 1;
    if (dir == 3)
        pos.second -= 1;
    hist.push_back(dir);
    if (hist.size() > 10 || map[pos.first][pos.second] == WALL ||
        map[pos.first][pos.second] == BLOCK ||
        map[pos.first][pos.second] == PLAYER ||
        map[pos.first][pos.second] == BOMB ||
        map[pos.first][pos.second] == IA ||
        map[pos.first][pos.second] == PASS ||
        map[pos.first][pos.second] == BOMBPLAYER) {
        hist.clear();
        return (hist);
    }
    if (danger[pos.first][pos.second] == 0)
        return (hist);
    std::vector<int> second = getMinToSafety(hist, pos, map, danger, dir);
    std::vector<int> first =
        getMinToSafety(hist, pos, map, danger, (dir + 1) % 4);
    std::vector<int> third =
        getMinToSafety(hist, pos, map, danger, (dir + 3) % 4);
    if ((second.size() != 0 && second.size() < first.size()) ||
        (first.size() == 0 && second.size() > 0))
        first = second;
    if ((third.size() != 0 && third.size() < first.size()) ||
        (first.size() == 0 && third.size() > 0))
        first = third;
    return (first);
}

void Bot::defenseDest(std::vector<std::vector<int>> map,
                      std::vector<std::vector<int>> danger)
{
    std::vector<int> tmp;
    std::vector<int> up = getMinToSafety(tmp, _pos, map, danger, 0);
    std::vector<int> right = getMinToSafety(tmp, _pos, map, danger, 1);
    std::vector<int> down = getMinToSafety(tmp, _pos, map, danger, 2);
    std::vector<int> left = getMinToSafety(tmp, _pos, map, danger, 3);

    _dest = up;
    if ((right.size() != 0 && right.size() < _dest.size()) ||
        (_dest.size() == 0 && right.size() > 0))
        _dest = right;
    if ((left.size() != 0 && left.size() < _dest.size()) ||
        (_dest.size() == 0 && left.size() > 0))
        _dest = left;
    if ((down.size() != 0 && down.size() < _dest.size()) ||
        (_dest.size() == 0 && down.size() > 0))
        _dest = down;
}

void Bot::newDest(std::vector<std::vector<int>> map,
                  std::vector<std::vector<int>> danger)
{
    _dest.clear();
    if (danger[_pos.first][_pos.second] == 1) {
        defenseDest(map, danger);
        _defense = true;
    } else {
        offenceDest(map);
        _defense = false;
    }
    _getNewDest = false;
}

std::pair<int, int> Bot::getPlayerPos(std::vector<std::vector<int>> map) const
{
    std::pair<int, int> res = {0, 0};
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == PLAYER) {
                res.first = i;
                res.second = j;
                return (res);
            }
        }
    }
    return (res);
}

// nombre de block a porté de destruction
int Bot::getNbrBlock(std::vector<std::vector<int>> map)
{
    int res = 0;

    for (int i = 0;
         i <= _power && _pos.second + i < (int)map[_pos.first].size(); i++) {
        if (map[_pos.first][_pos.second + i] == WALL)
            break;
        if (map[_pos.first][_pos.second + i] == BLOCK) {
            res += 1;
            break;
        }
    }
    for (int i = 0; i <= _power && _pos.second - i >= 0; i++) {
        if (map[_pos.first][_pos.second - i] == WALL)
            break;
        if (map[_pos.first][_pos.second - i] == BLOCK) {
            res += 1;
            break;
        }
    }
    for (int i = 0; i <= _power && _pos.first + i < (int)map.size(); i++) {
        if (map[_pos.first + i][_pos.second] == WALL)
            break;
        if (map[_pos.first + i][_pos.second] == BLOCK) {
            res += 1;
            break;
        }
    }
    for (int i = 0; i <= _power && _pos.first - i >= 0; i++) {
        if (map[_pos.first - i][_pos.second] == WALL)
            break;
        if (map[_pos.first - i][_pos.second] == BLOCK) {
            res += 1;
            break;
        }
    }
    return (res);
}

bool Bot::checkHitPlayer(std::pair<int, int> playerPos)
{
    int x = playerPos.first - _pos.first;
    int y = playerPos.second - _pos.second;

    if (x != 0 && y != 0)
        return (false);
    if (abs(x + y) > _power)
        return (false);
    return (true);
}

void Bot::setGetNewDest(bool ne)
{
    _getNewDest = ne;
}

std::vector<int> Bot::getDest() const
{
    return (_dest);
}

bool Bot::getDefense() const
{
    return (_defense);
}

void Bot::removeTopDest()
{
    _dest.erase(_dest.begin());
}

void Bot::setDest(std::vector<int> dest)
{
    _dest = dest;
}

bool Bot::getGetNewDest() const
{
    return (_getNewDest);
}

void Bot::setPos(int x, int y)
{
    _pos = std::make_pair(x, y);
}

void Bot::move(int x, int y)
{
    _pos.first = x;
    _pos.second = y;
}

void Bot::addBomb(int x, int y)
{
    _bombs.push_back(std::make_unique<Bomb>(x, y));
}

int Bot::getBombs() const
{
    return (_bombs.size());
}

std::pair<int, int> Bot::getPos() const
{
    return _pos;
}

std::pair<int, int> Bot::getBombPos(int bomb) const
{
    return _bombs[bomb]->getPos();
}

float Bot::getBombSecond(int bomb) const
{
    return _bombs[bomb]->getSecond();
}

int Bot::getMax() const
{
    return _bomb;
}

bool Bot::getWallPass()
{
    return _pass;
}

bool Bot::getAlive() const
{
    return _alive;
}

void Bot::setAlive(bool n)
{
    _alive = n;
}

void Bot::removeBomb(int bomb)
{
    _bombs.erase(_bombs.begin() + bomb);
}

int Bot::getPower() const
{
    return _power;
}

void Bot::upBomb()
{
    _bomb += 1;
}

void Bot::upPower()
{
    _power += 1;
}

void Bot::upSpeed()
{
    _speed += 1;
}

void Bot::wallPass()
{
    _pass = true;
}
