/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_
#include <ctime>
#include <memory>
#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <fstream>
#include <iostream>

/*!
    Map Enumeration
*/
enum MapEnum {
    VOID = 0,   /// Free space
    WALL,       /// Indestructible wall
    BLOCK,      /// Destructible wall
    PLAYER,     /// You
    BOMB,       /// Bomb in free space
    FIRE,       /// Explosion in free case
    IA,         /// Computer ennemy
    DESTROY,    /// Explosion in wall destroy
    SPEED,      /// Speed Up
    WALLPASS,   /// Wall Pass
    POWER,      /// Fire Up
    UPBOMB,     /// Bomb Up
    PASS,       /// You and wall destructible on the same case
    BOMBPLAYER, /// You and bomb on the same case
    BOMBIA      /// You and bomb on the same case
};

/*!
    Key Enumeration
*/
enum KeyEnum {
    UP = 0,    /// Z Move up
    RIGHT,     /// D Move right
    DOWN,      /// S Move down
    LEFT,      /// Q Move left
    ENTER,     /// Enter Run selected
    SPACE,     /// Open menu
    UNDEFINED, /// No Key Pressed
};

/// Used by the core to check the state of the game
///
enum WinCondition { WIN, LOSE, NOT_ENDED };

/*!
    Game interface
*/
class IGames {
public:
    /// Virtual destructor
    ///
    /// @returns nothing
    ///
    virtual ~IGames() = default;
    /// Init every variables needed by the game
    ///
    /// @returns nothing
    ///
    virtual void init() = 0;
    /// Exit the game
    ///
    /// @returns nothing
    ///
    virtual void exit() = 0;
    /// Get the state of the game
    ///
    /// @returns WinCondition to determine if the game is ended or not
    ///
    virtual WinCondition loop() = 0;
    /// Get the map of the game
    ///
    /// @returns Map in a two dimensional vector
    ///
    virtual std::vector<std::vector<int>> &getMap() const = 0;
    /// Get the score of the game
    ///
    /// @returns Current score in the game
    ///
    virtual int getScore() const = 0;
    /// Send the input of the core to the game to determine the action to do
    /// @param KeyNum& The key pressed by the player
    /// @returns nothing
    ///
    virtual void getKey(KeyEnum) = 0;
    /// Return the name of the game
    ///
    /// @returns std::string name
    ///
    virtual std::string getName() const = 0;

protected:
private:
};

#endif /* !IGAMES_HPP_ */
