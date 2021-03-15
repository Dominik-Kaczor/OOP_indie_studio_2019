/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "IGames.hpp"
#include "Bomb.hpp"

class Player {
public:
    /// Init player
    ///
    /// @returns nothing
    ///
    Player();
    /// Destroy player
    ///
    /// @returns nothing
    ///
    ~Player();
    /// Move player
    /// @param X position
    /// @param Y positin
    /// @returns nothing
    ///
    void move(int, int);
    /// Get position of the player
    ///
    /// @returns std::pair<int, int> => (x, y) position
    ///
    std::pair<int, int> getPos() const;
    /// Add bomb at position
    /// @param X position
    /// @param Y position
    /// @returns nothing
    ///
    void addBomb(int, int);
    /// Get number of bombs
    /// @returns nothing
    ///
    int getBombs() const;
    /// Get if the player is dead
    /// @returns bool
    ///
    bool getDead() const;
    /// Set player dead
    /// @returns nothing
    ///
    void modifyDead();
    /// Get maximum number of bombs
    /// @returns maximum number of bombs
    ///
    int getMax() const;
    /// Load informations about the player
    /// @param File
    /// @returns nothing
    ///
    void loadInfos(std::ifstream &file);
    /// Save informations about the player
    /// @param File
    /// @returns nothing
    ///
    void saveInfos(std::ofstream &file);
    /// Str to word array in cpp
    /// @param std::string string to split
    /// @param char delimiter
    /// @returns std::vector<std::string>
    ///
    std::vector<std::string> split(const std::string &, char);
    /// Get position (x / y) of a specific bomb
    /// @param bomb id
    /// @returns positions
    ///
    std::pair<int, int> getBombPos(int) const;
    /// Get time of a bomb
    /// @param bomb id
    /// @returns time
    ///
    float getBombSecond(int) const;
    /// Remove bomb by id
    /// @param bomb id
    /// @returns nothing
    ///
    void removeBomb(int);
    /// Get power of player
    /// @returns power
    ///
    int getPower() const;
    /// Set bonus up to player
    /// @returns nothing
    ///
    void upPower();
    /// Set bonus up bomb to player
    /// @returns nothing
    ///
    void upBomb();
    /// Set bonus speed up to player
    /// @returns nothing
    ///
    void upSpeed();
    /// Set bonus wall pass to player
    /// @returns nothing
    ///
    void wallPass();
    /// Check if player can wall pass
    /// @returns bool
    ///
    bool getWallPass();

private:
    std::vector<std::unique_ptr<Bomb>> _bombs;
    std::pair<int, int> _pos;
    int _bomb;
    int _speed;
    int _power;
    bool _pass;
    bool _dead;
};

#endif /* !PLAYER_HPP_ */
