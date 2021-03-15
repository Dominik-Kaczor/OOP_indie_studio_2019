/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Engine
*/

#ifndef Engine_HPP_
#define Engine_HPP_
#include <iostream>
#include <map>
#include <irrlicht.h>
#include <IrrlichtDevice.h>
#include "Constants.hpp"
#include "IGames.hpp"
#include "Exceptions.hpp"
#include "MyEventReceiver.hpp"
#include "Image.hpp"
#include "Button.hpp"
#include "MeshType.hpp"
#include "Sound.hpp"

class Engine {
public:
    Engine();
    ~Engine() = default;
    void setupDevice();
    void setupDeviceMainMenu();
    void destroyDevice();
    void setDeviceTitle(const std::string &);
    void setVideoDriver();
    void setSceneManager();
    void setGuiEnv();
    void setSkin();
    void setupEngine();
    void setReceiver();
    void listenToReceiver(Events::Button::eventButton button);
    void listenToReceiver(Events::EditBox::eventEditBox editbox);
    void addImage(std::string);
    void addButton(Events::Button::eventButton button, std::string,
                   irr::core::rect<irr::s32> rect);
    void addEditBox(Events::EditBox::eventEditBox event, std::string content,
                    irr::core::rect<irr::s32> rect);
    void clearLastEditBoxEvent();
    void drawAllImages();
    void render() const;
    void clear() const;
    void draw() const;
    bool isRunning() const;
    void setFont(std::string path);
    void clearButtons();
    void clearImages();
    void addPlayers(std::vector<std::vector<int>> &map);
    irr::scene::IAnimatedMeshSceneNode *addAnimatedMesh(std::string path, int,
                                                        int);
    KeyEnum getKey();
    void applyTexture();
    int changeAnimation(int, int, irr::scene::IAnimatedMeshSceneNode *);
    void drawScene();
    void drawMap(std::vector<std::vector<int>>);
    void setLight();
    void movePlayer(std::vector<std::vector<int>> &map, KeyEnum key);
    void setCamera();
    void startScene();
    void modifyLast(std::vector<std::vector<int>>);
    void initMap(std::vector<std::vector<int>>);
    void addSound(const std::string &name, const std::string &path);
    void playSound(const std::string &name);
    void stopSound(const std::string &name);
    void addAndPlaySound(const std::string &name, const std::string &path);
    irr::scene::ISceneManager *getScene() const;
    Events::Button::eventButton getLastButtonEvent() const;
    Events::EditBox::eventEditBox getLastEditBoxEvent() const;
    irr::video::IVideoDriver *getVideoDriver() const;
    irr::IrrlichtDevice *getDevice() const;
    irr::gui::IGUIEnvironment *getEnv() const;
    std::map<int, std::map<int, irr::scene::ISceneNode *>> _nodes;
    std::map<int, irr::scene::IAnimatedMeshSceneNode *> _players;

protected:
private:
    std::vector<std::vector<int>> _last;
    irr::IrrlichtDevice *_device;
    irr::video::IVideoDriver *_driver;
    irr::scene::ISceneManager *_scene;
    irr::gui::IGUIEnvironment *_env;
    irr::gui::IGUISkin *_skin;
    MyEventReceiver _receiver;
    bool _isMoving;
    std::vector<Image> _images;
    std::vector<Button> _buttons;
    std::map<std::string, Sound> _sounds;
    int _actual;
};

#endif /* !Engine_HPP_ */
