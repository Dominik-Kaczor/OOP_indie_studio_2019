/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Bomberman
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <irrlicht.h>
#include <IrrlichtDevice.h>
#include "Constants.hpp"
#include "Exceptions.hpp"
#include "Engine.hpp"
#include "MyEventReceiver.hpp"
#include "Image.hpp"
#include "WString.hpp"
#include "Context.hpp"
#include "Bomberman.hpp"
#include "Timer.hpp"

class Core {
public:
    Core();
    ~Core() = default;
    int getExitStatus() const;
    void switchScene();
    void start();
    void splashScreenScene();
    void startMenuScene();
    void settingsMenuScene();
    bool pollEvent();
    void clear();
    void draw();
    void render();
    void gameScene();
    void endingScene(bool);

protected:
private:
    std::unique_ptr<Engine> _engine;
    std::unique_ptr<Bomberman> _game{new Bomberman};
    std::unique_ptr<Timer> _timer;
    int _exit_status;
    bool _is_running;
    int _last_event;
    std::string _player_name;
    Context::State _state;
};

#endif /* !CORE_HPP_ */
