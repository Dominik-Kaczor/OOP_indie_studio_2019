/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Bomberman
*/

#include "Bomberman.hpp"
#include <string>

void Bomberman::loadDangers()
{
    std::string line;
    int i = 0;

    std::getline(_load, line);
    while (line != "Emap") {
        for (size_t j = 0; j < line.size(); j++) {
            _dangers[i][j] = (int)line[j] - 48;
        }
        i++;
        std::getline(_load, line);
    }
    line.clear();
}

Bomberman::Bomberman(std::string save) : _load(save)
{
    std::string line;

    if (std::getline(_load, line)) {
        _name = line;
        _map->loadMap(_load);
        _player1->loadInfos(_load);
        initDangerMap();
        loadDangers();
        _bot1->loadInfos(_load);
        _bot2->loadInfos(_load);
        _bot3->loadInfos(_load);
        std::srand(std::time(nullptr));
    } else {
        _map->modifyMap(1, 1, PLAYER);
        _map->modifyMap(1, 17, IA);
        _bot1->setPos(1, 17);
        _map->modifyMap(11, 1, IA);
        _bot2->setPos(11, 1);
        _map->modifyMap(11, 17, IA);
        _bot3->setPos(11, 17);
        std::srand(std::time(nullptr));
        initDangerMap();
    }
}

Bomberman::Bomberman() : _name("Maz")
{
    _map->modifyMap(1, 1, PLAYER);
    _map->modifyMap(1, 17, IA);
    _bot1->setPos(1, 17);
    _map->modifyMap(11, 1, IA);
    _bot2->setPos(11, 1);
    _map->modifyMap(11, 17, IA);
    _bot3->setPos(11, 17);
    std::srand(std::time(nullptr));
    initDangerMap();
}

void Bomberman::initDangerMap()
{
    _dangers = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
}

Bomberman::~Bomberman()
{
    _save.close();
    _load.close();
}

void Bomberman::displayMap()
{
    _map->displayMap();
}

void Bomberman::exit()
{
}

void Bomberman::cleanCaseMap()
{
    if (_map->moveCheck(_player1->getPos().first, _player1->getPos().second) !=
            MapEnum::BOMB &&
        _map->moveCheck(_player1->getPos().first, _player1->getPos().second) !=
            MapEnum::BLOCK)
        _map->modifyMap(_player1->getPos().first, _player1->getPos().second,
                        VOID);
}

void Bomberman::move(int x, int y)
{
    int Case = _map->moveCheck(_player1->getPos().first + x,
                               _player1->getPos().second + y);

    if (Case != MapEnum::WALL && Case != MapEnum::BOMB && Case != MapEnum::IA && Case != BOMBIA) {
        if (_map->moveCheck(_player1->getPos().first,
                            _player1->getPos().second) == MapEnum::PASS)
            _map->modifyMap(_player1->getPos().first, _player1->getPos().second,
                            BLOCK);
        if (_map->moveCheck(_player1->getPos().first,
                            _player1->getPos().second) == MapEnum::BOMBPLAYER)
            _map->modifyMap(_player1->getPos().first, _player1->getPos().second,
                            BOMB);
        if (Case == MapEnum::SPEED)
            _player1->upSpeed();
        if (Case == MapEnum::POWER)
            _player1->upPower();
        if (Case == MapEnum::UPBOMB)
            _player1->upBomb();
        if (Case == MapEnum::WALLPASS)
            _player1->wallPass();
        if (_player1->getWallPass() == true && Case == MapEnum::BLOCK) {
            cleanCaseMap();
            _player1->move(_player1->getPos().first + x,
                           _player1->getPos().second + y);
            _map->modifyMap(_player1->getPos().first, _player1->getPos().second,
                            PASS);
        }
        if (Case != MapEnum::BLOCK && Case != MapEnum::PASS) {
            cleanCaseMap();
            _player1->move(_player1->getPos().first + x,
                           _player1->getPos().second + y);
            _map->modifyMap(_player1->getPos().first, _player1->getPos().second,
                            PLAYER);
        }
    }
}

void Bomberman::MoveBot(std::pair<int, int> pos, std::pair<int, int> newPos,
                        int which, bool defense)
{
    int Case = _map->moveCheck(newPos.first, newPos.second);
    int OldCase = _map->moveCheck(pos.first, pos.second);

    if (!defense && _dangers[newPos.first][newPos.second] == 1)
        return;
    if (Case == PLAYER || Case == IA || Case == BOMBIA || Case == BOMB ||
        Case == BOMBPLAYER || Case == PASS)
        return;
    if (Case == SPEED) {
        if (which == 1)
            _bot1->upSpeed();
        if (which == 2)
            _bot2->upSpeed();
        if (which == 3)
            _bot3->upSpeed();
    }
    if (Case == POWER) {
        if (which == 1)
            _bot1->upPower();
        if (which == 2)
            _bot2->upPower();
        if (which == 3)
            _bot3->upPower();
    }
    if (Case == UPBOMB) {
        if (which == 1)
            _bot1->upBomb();
        if (which == 2)
            _bot2->upBomb();
        if (which == 3)
            _bot3->upBomb();
    }
    if (Case == WALLPASS) {
        if (which == 1)
            _bot1->wallPass();
        if (which == 2)
            _bot2->wallPass();
        if (which == 3)
            _bot3->wallPass();
    }
    if (OldCase == BOMBIA) {
        _map->modifyMap(pos.first, pos.second, BOMB);
    } else {
        _map->modifyMap(pos.first, pos.second, VOID);
    }
    _map->modifyMap(newPos.first, newPos.second, IA);
    if (which == 1) {
        _bot1->removeTopDest();
        _bot1->setPos(newPos.first, newPos.second);
    }
    if (which == 2) {
        _bot2->removeTopDest();
        _bot2->setPos(newPos.first, newPos.second);
    }
    if (which == 3) {
        _bot3->removeTopDest();
        _bot3->setPos(newPos.first, newPos.second);
    }
}

void Bomberman::getNewDestBot()
{
    if (_bot1->getAlive())
        _bot1->setGetNewDest(true);
    if (_bot2->getAlive())
        _bot2->setGetNewDest(true);
    if (_bot3->getAlive())
        _bot3->setGetNewDest(true);
}

void Bomberman::getKey(KeyEnum command)
{
    if (command == KeyEnum::ENTER) {
        save();
    }
    if (command == KeyEnum::SPACE) {
        if (_player1->getBombs() < _player1->getMax() &&
            _map->moveCheck(_player1->getPos().first,
                            _player1->getPos().second) != MapEnum::PASS) {
            _map->modifyMap(_player1->getPos().first, _player1->getPos().second,
                            BOMBPLAYER);
            _player1->addBomb(_player1->getPos().first,
                              _player1->getPos().second);
            addBomb(_player1->getPos().first, _player1->getPos().second,
                    _player1->getPower());
            getNewDestBot();
        }
    }
    if (command == KeyEnum::RIGHT)
        move(0, 1);
    if (command == KeyEnum::LEFT)
        move(0, -1);
    if (command == KeyEnum::UP)
        move(-1, 0);
    if (command == KeyEnum::DOWN)
        move(1, 0);
    if (_bot1->getAlive()) {
        if (_bot1->getGetNewDest()) {
            _bot1->newDest(_map->getMap(), _dangers);
        }
        std::vector<int> dest = _bot1->getDest();
        if (dest.size() > 0) {
            int dir = dest[0];
            std::pair<int, int> newPos = _bot1->getPos();
            if (dir == 0)
                newPos.first -= 1;
            if (dir == 1)
                newPos.second += 1;
            if (dir == 2)
                newPos.first += 1;
            if (dir == 3)
                newPos.second -= 1;
            MoveBot(_bot1->getPos(), newPos, 1, _bot1->getDefense());
        } else {
            _bot1->setGetNewDest(true);
        }
        if (_bot1->getBombs() < _bot1->getMax() &&
            ((dest.size() <= 1 && !_bot1->getDefense()) ||
             _bot1->checkHitPlayer(_player1->getPos()))) {
            addBombBot(_bot1->getPos(), _bot1->getPower(), 1);
        }
    }
    if (_bot2->getAlive()) {
        if (_bot2->getGetNewDest()) {
            _bot2->newDest(_map->getMap(), _dangers);
        }
        std::vector<int> dest = _bot2->getDest();
        if (dest.size() > 0) {
            int dir = dest[0];
            std::pair<int, int> newPos = _bot2->getPos();
            if (dir == 0)
                newPos.first -= 1;
            if (dir == 1)
                newPos.second += 1;
            if (dir == 2)
                newPos.first += 1;
            if (dir == 3)
                newPos.second -= 1;
            MoveBot(_bot2->getPos(), newPos, 2, _bot2->getDefense());
        } else {
            _bot2->setGetNewDest(true);
        }
        if (_bot2->getBombs() < _bot2->getMax() &&
            ((dest.size() <= 1 && !_bot2->getDefense()) ||
             _bot2->checkHitPlayer(_player1->getPos()))) {
            addBombBot(_bot2->getPos(), _bot2->getPower(), 2);
        }
    }
    if (_bot3->getAlive()) {
        if (_bot3->getGetNewDest()) {
            _bot3->newDest(_map->getMap(), _dangers);
        }
        std::vector<int> dest = _bot3->getDest();
        if (dest.size() > 0) {
            int dir = dest[0];
            std::pair<int, int> newPos = _bot3->getPos();
            if (dir == 0)
                newPos.first -= 1;
            if (dir == 1)
                newPos.second += 1;
            if (dir == 2)
                newPos.first += 1;
            if (dir == 3)
                newPos.second -= 1;
            MoveBot(_bot3->getPos(), newPos, 3, _bot3->getDefense());
        } else {
            _bot3->setGetNewDest(true);
        }
        if (_bot3->getBombs() < _bot3->getMax() &&
            ((dest.size() <= 1 && !_bot3->getDefense()) ||
             _bot3->checkHitPlayer(_player1->getPos()))) {
            addBombBot(_bot2->getPos(), _bot3->getPower(), 3);
        }
    }
}

void Bomberman::addBombBot(std::pair<int, int> pos, int power, int which)
{
    if (which == 1)
        _bot1->addBomb(pos.first, pos.second);
    if (which == 2)
        _bot2->addBomb(pos.first, pos.second);
    if (which == 3)
        _bot3->addBomb(pos.first, pos.second);
    _map->modifyMap(pos.first, pos.second, BOMBIA);
    addBomb(pos.first, pos.second, power);
    getNewDestBot();
}

void Bomberman::addBomb(int x, int y, int power)
{
    std::vector<std::vector<int>> map = _map->getMap();

    _dangers[x][y] = 1;
    for (int i = 1; i <= power && y + i < int(map[x].size()); i++) {
        if (map[x][y + i] != WALL && map[x][y + i] != BLOCK &&
            map[x][y + i] != PASS)
            _dangers[x][y + i] = 1;
    }
    for (int i = 1; i <= power && y - i > 0; i++) {
        if (map[x][y - i] != WALL && map[x][y - i] != BLOCK &&
            map[x][y - i] != PASS)
            _dangers[x][y - i] = 1;
    }
    for (int i = 1; i <= power && x + i < int(map.size()); i++) {
        if (map[x + i][y] != WALL && map[x + i][y] != BLOCK &&
            map[x + i][y] != PASS)
            _dangers[x + i][y] = 1;
    }
    for (int i = 1; i <= power && x - i > 0; i++) {
        if (map[x - i][y] != WALL && map[x - i][y] != BLOCK &&
            map[x - i][y] != PASS)
            _dangers[x - i][y] = 1;
    }
}

void Bomberman::newDangerMap()
{
    initDangerMap();
    std::pair<int, int> tmp;
    for (int i = 0; i < _player1->getBombs(); i++) {
        tmp = _player1->getBombPos(i);
        addBomb(tmp.first, tmp.second, _player1->getPower());
    }
    for (int i = 0; i < _bot1->getBombs(); i++) {
        tmp = _bot1->getBombPos(i);
        addBomb(tmp.first, tmp.second, _bot1->getPower());
    }
    for (int i = 0; i < _bot2->getBombs(); i++) {
        tmp = _bot2->getBombPos(i);
        addBomb(tmp.first, tmp.second, _bot2->getPower());
    }
    for (int i = 0; i < _bot3->getBombs(); i++) {
        tmp = _bot3->getBombPos(i);
        addBomb(tmp.first, tmp.second, _bot3->getPower());
    }
}

void Bomberman::destroyBot(int x, int y)
{
    std::pair<int, int> tmp = _bot1->getPos();
    if (tmp.first == x && tmp.second == y) {
        _bot1->setAlive(false);
        return;
    }
    tmp = _bot2->getPos();
    if (tmp.first == x && tmp.second == y) {
        _bot2->setAlive(false);
        return;
    }
    tmp = _bot3->getPos();
    if (tmp.first == x && tmp.second == y) {
        _bot3->setAlive(false);
        return;
    }
}

bool Bomberman::destroyBlocks(int x, int y, bool liking)
{
    if (_map->moveCheck(x, y) == MapEnum::BOMB && liking == true) {
        for (int i = 0; i < _player1->getBombs(); i++) {
            if (_player1->getBombPos(i).first == x &&
                _player1->getBombPos(i).second == y) {
                Explosion(x, y, _player1->getPower());
                _player1->removeBomb(i);
            }
        }
    }
    if (_map->moveCheck(x, y) == MapEnum::IA ||
        _map->moveCheck(x, y) == MapEnum::BOMBIA)
        destroyBot(x, y);
    if (_map->moveCheck(x, y) == MapEnum::WALL)
        return false;
    if (_map->moveCheck(x, y) == MapEnum::PLAYER ||
        _map->moveCheck(x, y) == MapEnum::BOMBPLAYER)
        _player1->modifyDead();
    if (_map->moveCheck(x, y) == MapEnum::BLOCK) {
        _map->modifyMap(x, y, DESTROY);
        return false;
    } else
        _map->modifyMap(x, y, FIRE);
    return true;
}

void Bomberman::Explosion(int x, int y, int power)
{
    destroyBlocks(x, y, false);
    for (int i = 1; i <= power; i++)
        if (destroyBlocks(x, y + i, true) == false)
            break;
    for (int i = 1; i <= power; i++)
        if (destroyBlocks(x, y - i, true) == false)
            break;
    for (int i = 1; i <= power; i++)
        if (destroyBlocks(x - i, y, true) == false)
            break;
    for (int i = 1; i <= power; i++)
        if (destroyBlocks(x + i, y, true) == false)
            break;
}

void Bomberman::saveDangers()
{
    _save << "Dangers" << std::endl;
    for (size_t i = 0; i < _dangers.size(); i++) {
        for (size_t j = 0; j < _dangers[i].size(); j++) {
            _save << _dangers[i][j];
        }
        _save << std::endl;
    }
    _save << "Emap" << std::endl;
}

void Bomberman::save()
{
    _save.open(".save");
    _save << _name << std::endl;
    _map->saveMap(_save);
    _player1->saveInfos(_save);
    saveDangers();
    _bot1->saveInfos(_save);
    _bot2->saveInfos(_save);
    _bot3->saveInfos(_save);
    _save.close();
}

void Bomberman::randomAbilities(int x, int y)
{
    int randvar = std::rand() % 100;

    if (randvar >= 1 && randvar <= 9) {
        _map->modifyMap(x, y, POWER);
        return;
    }
    if (randvar >= 31 && randvar <= 39) {
        _map->modifyMap(x, y, SPEED);
        return;
    }
    if (randvar >= 61 && randvar <= 69) {
        _map->modifyMap(x, y, UPBOMB);
        return;
    }
    if (randvar == 0 || randvar == 100) {
        _map->modifyMap(x, y, WALLPASS);
        return;
    }
    _map->modifyMap(x, y, VOID);
}

void Bomberman::removeExplosion()
{
    for (size_t i = 0; i < _map->getMap().size(); i++) {
        for (size_t j = 0; j < _map->getMap()[i].size(); j++) {
            if (_map->moveCheck(i, j) == FIRE)
                _map->modifyMap(i, j, VOID);
            if (_map->moveCheck(i, j) == DESTROY)
                randomAbilities(i, j);
        }
    }
}

WinCondition Bomberman::loop()
{
    removeExplosion();
    if (_player1->getDead()) {
        return WinCondition::LOSE;
    }
    if (!_bot1->getAlive() && !_bot2->getAlive() && !_bot3->getAlive()) {
        return WinCondition::WIN;
    }
    for (int i = 0; i < _player1->getBombs(); i++) {
        if (_player1->getBombSecond(i) >= 1) {
            Explosion(_player1->getBombPos(i).first,
                      _player1->getBombPos(i).second, _player1->getPower());
            std::cout << "-------------------" << std::endl;
            displayMap();
            std::cout << "----" << std::endl;
            _player1->removeBomb(i);
            newDangerMap();
            getNewDestBot();
            displayMap();
        }
    }
    for (int i = 0; i < _bot1->getBombs(); i++) {
        if (_bot1->getBombSecond(i) >= 1) {
            Explosion(_bot1->getBombPos(i).first, _bot1->getBombPos(i).second,
                      _bot1->getPower());
            _bot1->removeBomb(i);
            newDangerMap();
            getNewDestBot();
        }
    }
    for (int i = 0; i < _bot2->getBombs(); i++) {
        if (_bot2->getBombSecond(i) >= 1) {
            Explosion(_bot2->getBombPos(i).first, _bot2->getBombPos(i).second,
                      _bot2->getPower());
            _bot2->removeBomb(i);
            newDangerMap();
            getNewDestBot();
        }
    }
    for (int i = 0; i < _bot3->getBombs(); i++) {
        if (_bot3->getBombSecond(i) >= 1) {
            Explosion(_bot3->getBombPos(i).first, _bot3->getBombPos(i).second,
                      _bot3->getPower());
            _bot3->removeBomb(i);
            newDangerMap();
            getNewDestBot();
        }
    }
    return WinCondition::NOT_ENDED;
}

std::vector<std::vector<int>> &Bomberman::getMap() const
{
    return _map->getMap();
}

int Bomberman::getScore() const
{
    return 0;
}

void Bomberman::init()
{
}

std::string Bomberman::getName() const
{
    return "Player";
}
