/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Core
*/

#include "Core.hpp"
#include <SFML/Audio.hpp>

Core::Core()
{
    this->_last_event = 0;
    this->_exit_status = 0;
    this->_is_running = true;
}

void Core::start()
{
    try {
        this->_engine = std::make_unique<Engine>();
        this->_game = std::make_unique<Bomberman>();
        this->_timer = std::make_unique<Timer>();
        this->_engine->setupEngine();
    } catch (Exceptions &error) {
        throw Exceptions(Constants::Engine::ERROR_DEVICE);
    }
    this->_engine->setVideoDriver();
    this->_engine->setGuiEnv();
}

bool Core::pollEvent()
{
    switch (this->_state) {
    case Context::State::SPLASHSCREEN:
        break;
    case Context::State::MAIN_MENU:
        if (this->_engine->getLastButtonEvent() ==
            Events::Button::eventButton::GUI_QUIT_BUTTON) {
            this->_is_running = false;
            this->_engine->destroyDevice();
            std::exit(84);
        }
        if (this->_engine->getLastButtonEvent() ==
            Events::Button::eventButton::GUI_SETTINGS_BUTTON) {
            this->_last_event =
                Events::Button::eventButton::GUI_SETTINGS_BUTTON;
            return (true);
        }
        if (this->_engine->getLastButtonEvent() ==
            Events::Button::eventButton::GUI_PLAY_BUTTON) {
            this->_last_event = Events::Button::eventButton::GUI_PLAY_BUTTON;
            return (true);
        }
        if (this->_engine->getLastButtonEvent() ==
            Events::Button::eventButton::GUI_LOAD_BUTTON) {
            this->_last_event = Events::Button::eventButton::GUI_LOAD_BUTTON;
            return (true);
        }
        break;
    case Context::State::SETTINGS:
        if (this->_engine->getLastButtonEvent() ==
            Events::Button::eventButton::GUI_SETTINGS_GO_BACK) {
            return (true);
        }
        if (this->_engine->getLastEditBoxEvent() ==
            Events::EditBox::eventEditBox::EDIT_USERNAME) {
            this->_player_name = Wrapper::convertString(
                this->_engine->getEnv()
                    ->getRootGUIElement()
                    ->getElementFromId(
                        Events::EditBox::eventEditBox::EDIT_USERNAME, true)
                    ->getText());
            this->_engine->clearLastEditBoxEvent();
        }
        break;
    case Context::State::PAUSE:
    case Context::State::IN_GAME:
        break;
    }
    return (false);
}

void Core::splashScreenScene()
{
    this->_engine->setSceneManager();
    this->_state = Context::State::SPLASHSCREEN;
    this->_engine->addImage(Constants::Assets::SPLASHSCREEN);
    irr::u32 last = this->_engine->getDevice()->getTimer()->getTime();
    while (this->_engine->getDevice()->run() && this->_is_running == true) {
        if (this->_engine->getDevice()->getTimer()->getTime() > (last + 2000))
            break;
        this->clear();
        this->draw();
        this->render();
        this->pollEvent();
    }
    this->switchScene();
    this->startMenuScene();
}

void Core::switchScene()
{
    this->_engine->destroyDevice();
    this->_engine->setupDeviceMainMenu();
    this->_engine->setVideoDriver();
    this->_engine->setGuiEnv();
    this->_engine->setFont(Constants::Assets::FONT);
}

void Core::startMenuScene()
{
    this->_engine->addAndPlaySound(Constants::Sounds::Menu::NAME,
                                   Constants::Sounds::Menu::PATH);
    this->_state = Context::State::MAIN_MENU;
    this->_engine->getEnv()->clear();
    this->_engine->setDeviceTitle(Constants::MainMenu::DEVICE_TITLE);
    this->_engine->setReceiver();
    this->_engine->addButton(Events::Button::eventButton::GUI_PLAY_BUTTON,
                             Constants::MainMenu::BUTTON_PLAY,
                             Constants::MainMenu::START_BUTTON);
    this->_engine->addButton(Events::Button::eventButton::GUI_LOAD_BUTTON,
                             Constants::MainMenu::BUTTON_LOAD,
                             Constants::MainMenu::LOAD_BUTTON);
    this->_engine->addButton(Events::Button::eventButton::GUI_SETTINGS_BUTTON,
                             Constants::MainMenu::BUTTON_SETTINGS,
                             Constants::MainMenu::SETTINGS_BUTTON);
    this->_engine->addButton(Events::Button::eventButton::GUI_QUIT_BUTTON,
                             Constants::MainMenu::BUTTON_QUIT,
                             Constants::MainMenu::QUIT_BUTTON);
    this->_engine->addImage(Constants::Assets::MENU_BACKGROUND);

    while (this->_engine->getDevice()->run() && this->_is_running == true) {
        this->clear();
        this->_engine->drawAllImages();
        this->_engine->draw();
        this->render();
        if (this->pollEvent() == true)
            break;
    }
    if (this->_last_event == Events::Button::eventButton::GUI_SETTINGS_BUTTON) {
        this->_last_event = Events::Button::eventButton::NONE;
        this->settingsMenuScene();
        return;
    }
    if (this->_last_event == Events::Button::eventButton::GUI_PLAY_BUTTON) {
        this->_last_event = Events::Button::eventButton::NONE;
        this->_engine->stopSound(Constants::Sounds::Menu::NAME);
        this->gameScene();
        return;
    }
    if (this->_last_event == Events::Button::eventButton::GUI_LOAD_BUTTON) {
        this->_last_event = Events::Button::eventButton::NONE;
        this->_engine->stopSound(Constants::Sounds::Menu::NAME);
        this->_game.reset();
        this->_game = std::make_unique<Bomberman>(".save");
        this->gameScene();
        return;
    }
}

void Core::settingsMenuScene()
{
    this->_state = Context::State::SETTINGS;
    this->_engine->setDeviceTitle(Constants::Settings::DEVICE_TITLE);
    this->_engine->getEnv()->clear();
    this->_engine->addButton(Events::Button::eventButton::GUI_SETTINGS_GO_BACK,
                             Constants::Settings::BUTTON_BACK,
                             Constants::MainMenu::SETTINGS_QUIT);
    this->_engine->addEditBox(Events::EditBox::eventEditBox::EDIT_USERNAME,
                              Constants::Settings::INPUT,
                              Constants::MainMenu::SETTINGS_BUTTON);
    this->_engine->addImage(Constants::Assets::MENU_BACKGROUND);

    while (this->_engine->getDevice()->run() && this->_is_running == true) {
        this->clear();
        this->draw();
        this->render();
        if (this->pollEvent() == true)
            break;
    }
    this->startMenuScene();
}

void Core::gameScene()
{
    this->_engine->addAndPlaySound(Constants::Sounds::LetsGo::NAME,
                                   Constants::Sounds::LetsGo::PATH);
    this->_engine->addAndPlaySound(Constants::Sounds::IG::NAME,
                                   Constants::Sounds::IG::PATH);

    KeyEnum key;
    this->_engine->setSceneManager();
    this->_engine->setDeviceTitle(Constants::InGame::DEVICE_TITLE);
    this->_engine->addImage(Constants::Assets::GAME_BACKGROUND);
    this->_engine->setLight();
    this->_engine->setCamera();
    this->_engine->addPlayers(this->_game->getMap());
    this->_engine->initMap(this->_game->getMap());
    this->_engine->modifyLast(this->_game->getMap());
    this->_timer->setThen(this->_engine->getDevice()->getTimer()->getTime());
    while (this->_engine->getDevice()->run() && this->_is_running == true) {
        this->_timer->setNow(this->_engine->getDevice()->getTimer()->getTime());
        this->_timer->setFrameDeltaTime((irr::f32)(this->_timer->getNow() - this->_timer->getThen()) / 1000.f);
        if (this->_timer->getFrameDeltaTime() >= 0.1) {
            this->_engine->drawMap(this->_game->getMap());
            this->_engine->modifyLast(this->_game->getMap());
            this->_engine->startScene();
            key = this->_engine->getKey();
            this->_game->getKey(key);
            this->_timer->reset();
            if (this->_game->loop() == WinCondition::LOSE)
                this->endingScene(false);
            if (this->_game->loop() == WinCondition::WIN)
                this->endingScene(true);
            this->_engine->drawMap(this->_game->getMap());
            this->_engine->movePlayer(this->_game->getMap(), key);
            this->_engine->drawAllImages();
            this->_engine->getScene()->drawAll();
            this->_engine->getVideoDriver()->endScene();
            this->_engine->clear();
        }
    }
}

void Core::endingScene(bool win)
{
    irr::video::ITexture *image =
        this->_engine->getVideoDriver()->getTexture("./Assets/BlackScreen.jpg");
    irr::video::ITexture *P1 =
        this->_engine->getVideoDriver()->getTexture("./Assets/Win.png");
    irr::video::ITexture *P2 =
        this->_engine->getVideoDriver()->getTexture("./Assets/Lose.png");
    irr::video::ITexture *bomber = this->_engine->getVideoDriver()->getTexture(
        "./Assets/BomberSprite.png");
    irr::video::ITexture *msg =
        this->_engine->getVideoDriver()->getTexture("./Assets/PressSpace.png");
    irr::s32 backpos = 0;
    irr::s32 pos = 1930;
    while (this->_engine->getDevice()->run()) {
        this->_engine->getVideoDriver()->beginScene(
            true, true, irr::video::SColor(255, 100, 101, 140));
        this->_engine->getVideoDriver()->draw2DImage(
            image, irr::core::position2d<irr::s32>(0, 200),
            irr::core::rect<irr::s32>(0, 0, backpos, 540), 0,
            Constants::Engine::WHITE, true);
        if (backpos != 1930)
            backpos = backpos + 15;
        if (backpos >= 1930) {
            if (win) {
                this->_engine->getVideoDriver()->draw2DImage(
                    P1, irr::core::position2d<irr::s32>(960, 210),
                    irr::core::rect<irr::s32>(0, 0, 322, 87), 0,
                    Constants::Engine::WHITE, true);
            } else {
                this->_engine->getVideoDriver()->draw2DImage(
                    P2, irr::core::position2d<irr::s32>(960, 210),
                    irr::core::rect<irr::s32>(0, 0, 396, 89), 0,
                    Constants::Engine::WHITE, true);
            }
            this->_engine->getVideoDriver()->draw2DImage(
                bomber, irr::core::position2d<irr::s32>(pos, 240),
                irr::core::rect<irr::s32>(0, 0, 361, 400), 0,
                Constants::Engine::WHITE, true);
            if (pos >= 400)
                pos -= 20;
            this->_engine->getVideoDriver()->draw2DImage(
                msg, irr::core::position2d<irr::s32>(960, 600),
                irr::core::rect<irr::s32>(0, 0, 290, 21), 0,
                Constants::Engine::WHITE, true);
        }
        this->_engine->getVideoDriver()->endScene();
    }
}

int Core::getExitStatus() const
{
    return (this->_exit_status);
}

void Core::clear()
{
    this->_engine->clear();
}

void Core::draw()
{
    this->_engine->drawAllImages();
    this->_engine->draw();
    this->_engine->drawScene();
}

void Core::render()
{
    this->_engine->render();
}
