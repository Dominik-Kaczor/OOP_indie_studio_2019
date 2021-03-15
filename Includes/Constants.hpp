/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Constants
*/

#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_
#include <irrlicht.h>
#include <map>
#include "IGames.hpp"

namespace Constants {
    namespace Engine {
        static const int SPLASH_WINDOWS_SIZE_X = 424;
        static const int SPLASH_WINDOWS_SIZE_Y = 219;
        static const int WINDOWS_SIZE_X = 1920;
        static const int WINDOWS_SIZE_Y = 1080;
        static const irr::video::E_DRIVER_TYPE OPENGL_ENGINE =
            irr::video::EDT_OPENGL;
        static const int DEFAULT_BITS = 16;
        static const bool SPLASH_IS_FULLSCREEN = false;
        static const bool IS_FULLSCREEN = false;
        static const std::string &MAIN_MENU_TITLE = "Bomberman - Loading";
        static const std::string &ERROR_DEVICE = "Error in device";
    }; // namespace Engine
    namespace MainMenu {
        static const std::string &DEVICE_TITLE = "Bomberman - Main Menu";
        static const std::string &BUTTON_PLAY = "Play";
        static const std::string &BUTTON_SETTINGS = "Settings";
        static const std::string &BUTTON_QUIT = "Quit";
        static const std::string &BUTTON_LOAD = "Load";
        static const irr::core::rect<irr::s32> START_BUTTON(10, 100, 310,
                                                            100 + 64);
        static const irr::core::rect<irr::s32> SETTINGS_BUTTON(10, 200, 310,
                                                               200 + 64);
        static const irr::core::rect<irr::s32> QUIT_BUTTON(10, 300, 310,
                                                           300 + 64);
        static const irr::core::rect<irr::s32> SETTINGS_QUIT(10, 20, 310,
                                                             20 + 64);
        static const irr::core::rect<irr::s32> LOAD_BUTTON(10, 20, 310,
                                                             20 + 64);
    }; // namespace MainMenu
    namespace Settings {
        static const std::string &DEVICE_TITLE = "Bomberman - Settings";
        static const std::string &BUTTON_BACK = "Back";
        static const std::string &INPUT = "Player";
    }; // namespace Settings
    namespace InGame {
        static const std::string &DEVICE_TITLE = "Bomberman - In Game";
        namespace Assets {
            static const std::map<MapEnum, std::string> TEXTURES = {
                {MapEnum::WALL, "./Assets/Wall.png"},
                {MapEnum::BLOCK, "./Assets/Block.png"},
                {MapEnum::BOMB, "./Assets/TNT.jpg"},
                {MapEnum::FIRE, "./Assets/Fire.jpg"},
                {MapEnum::DESTROY, "./Assets/Fire.jpg"},
                {MapEnum::SPEED, "./Assets/Speed.png"},
                {MapEnum::WALLPASS, "./Assets/Pass.png"},
                {MapEnum::POWER, "./Assets/Power.png"},
                {MapEnum::UPBOMB, "./Assets/BombUp.png"},
            };
            static const std::string &DEFAULT = "./Assets/Grass.jpg";
            static const int DEFAULT_BLOCK_SIZE = 20;
        }; // namespace Assets
    };     // namespace InGame
    namespace File {
        static const std::string &ERROR_NO_ASSETS_FILE =
            "No assets file. Aborting";
        static const std::string &FILE_DOESNT_EXISTS =
            " doesn't exist, aborting.";
        static const std::string &FILE_EXISTS = " exists.";
        static const std::string &EXCEPTION = "Exception in assets loading";
    }; // namespace File
    namespace Assets {
        static const std::string &SPLASHSCREEN = "Assets/Splash.png";
        static const std::string &FONT = "Assets/Font.xml";
        static const std::string &MENU_BACKGROUND = "Assets/Background.jpg";
        static const std::string &GAME_BACKGROUND = "Assets/Background_IG.jpg";
        static const std::string &BOMBERBLACK = "Assets/BomberBlack";
        static const std::string &BLACKSCREEN = "./Assets/BlackScreen.jpg";
        static const std::string &WIN = "./Assets/Win.png";
        static const std::string &LOSE = "./Assets/Lose.png";
        static const std::string &BOMBERSPRITE = "./assets/BomberSprite.png";
        static const std::string &PRESS_SPACE = "./Assets/PressSpace.png";
    }; // namespace Assets
    namespace Sounds {
        namespace Menu {
            static const std::string &NAME = "MainMenu";
            static const std::string &PATH = "./Assets/MainMenuMusic.ogg";
        }; // namespace Menu
        namespace LetsGo {
            static const std::string &NAME = "LetsGo";
            static const std::string &PATH = "./Assets/LetsGo.ogg";
        }; // namespace LetsGo
        namespace IG {
            static const std::string &NAME = "IG";
            static const std::string &PATH = "./Assets/InGameMusic.ogg";
        }; // namespace IG
    };     // namespace Sounds
    namespace Engine {
        static const irr::video::SColor WHITE(255, 255, 255, 255);
    }
    static const int ERROR = 84;
    static const int SUCCESS = 0;
} // namespace Constants

#endif /* !CONSTANTS_HPP_ */
