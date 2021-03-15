/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Bomberman
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include "IGames.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Bot.hpp"

class Bomberman : public IGames {
public:
    Bomberman(std::string save);
    Bomberman();
    ~Bomberman();
    void randomAbilities(int, int);
    void displayMap();
    void init();
    void exit();
    void move(int, int);
    void MoveBot(std::pair<int, int>, std::pair<int, int>, int, bool);
    bool destroyBlocks(int, int, bool);
    void Explosion(int, int, int);
    void save();
    void getKey(KeyEnum);
    void cleanCaseMap();
    WinCondition loop();
    std::vector<std::vector<int>> &getMap() const;
    int getScore() const;
    std::string getName() const;
    void removeExplosion();
    void saveDangers();
    void loadDangers();
    void addBomb(int, int, int);
    void addBombBot(std::pair<int, int>, int, int);
    void initDangerMap();
    void newDangerMap();
    void getNewDestBot();
    void destroyBot(int, int);

private:
    std::unique_ptr<Map> _map{new Map};
    std::unique_ptr<Player> _player1{new Player};
    std::unique_ptr<Bot> _bot1{new Bot};
    std::unique_ptr<Bot> _bot2{new Bot};
    std::unique_ptr<Bot> _bot3{new Bot};
    std::vector<std::vector<int>> _dangers;
    std::string _name;
    std::ifstream _load;
    std::ofstream _save;
};

#endif /* !BOMBERMAN_HPP_ */
