/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine() : _isMoving(false), _actual(0)
{
}

void Engine::setupDevice()
{
    this->_device = irr::createDevice(
        Constants::Engine::OPENGL_ENGINE,
        irr::core::dimension2d<irr::u32>(
            Constants::Engine::SPLASH_WINDOWS_SIZE_X,
            Constants::Engine::SPLASH_WINDOWS_SIZE_Y),
        Constants::Engine::DEFAULT_BITS,
        Constants::Engine::SPLASH_IS_FULLSCREEN, false, false, &this->_receiver);
    if (!this->_device)
        throw Exceptions(Constants::Engine::ERROR_DEVICE);
}

void Engine::setupDeviceMainMenu()
{
    this->_device = irr::createDevice(
        Constants::Engine::OPENGL_ENGINE,
        irr::core::dimension2d<irr::u32>(Constants::Engine::WINDOWS_SIZE_X,
                                         Constants::Engine::WINDOWS_SIZE_Y),
        Constants::Engine::DEFAULT_BITS, Constants::Engine::IS_FULLSCREEN,
        false, false, &this->_receiver);
    if (!this->_device)
        throw Exceptions(Constants::Engine::ERROR_DEVICE);
}

void Engine::setupEngine()
{
    try {
        this->setupDevice();
        this->setDeviceTitle(Constants::Engine::MAIN_MENU_TITLE);
    } catch (Exceptions &error) {
        throw Exceptions(error);
    }
}

bool Engine::isRunning() const
{
    return (this->_device->run() && this->_device->isWindowActive());
}

void Engine::setDeviceTitle(const std::string &title)
{
    std::wstring w_title = std::wstring(title.begin(), title.end());
    this->_device->setWindowCaption(w_title.c_str());
}

void Engine::destroyDevice()
{
    this->_device->drop();
    this->_images.clear();
}

irr::IrrlichtDevice *Engine::getDevice() const
{
    return (this->_device);
}

void Engine::setVideoDriver()
{
    this->_driver = this->_device->getVideoDriver();
}

void Engine::setSceneManager()
{
    this->_scene = this->_device->getSceneManager();
}

irr::video::IVideoDriver *Engine::getVideoDriver() const
{
    return (this->_driver);
}

void Engine::setGuiEnv()
{
    this->_env = this->_device->getGUIEnvironment();
}

void Engine::setSkin()
{
    this->_skin = this->_env->getSkin();
}

void Engine::setFont(std::string path)
{
    std::wstring w_path = std::wstring(path.begin(), path.end());
    irr::gui::IGUIEnvironment *irrGUI = this->_device->getGUIEnvironment();
    irr::gui::IGUIFont *fnt = irrGUI->getFont(w_path.c_str());
    irrGUI->getSkin()->setFont(fnt);
}

void Engine::clear() const
{
    this->_driver->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
}

void Engine::modifyLast(std::vector<std::vector<int>> map)
{
    this->_last = map;
}

void Engine::draw() const
{
    this->_env->drawAll();
}

void Engine::render() const
{
    this->_driver->endScene();
}

irr::gui::IGUIEnvironment *Engine::getEnv() const
{
    return (this->_env);
}

void Engine::setReceiver()
{
    this->_device->setEventReceiver(&this->_receiver);
}

void Engine::listenToReceiver(Events::Button::eventButton button)
{
    this->_receiver.addButtonEvent(button);
}

void Engine::listenToReceiver(Events::EditBox::eventEditBox editbox)
{
    this->_receiver.addEditBoxEvent(editbox);
}

Events::Button::eventButton Engine::getLastButtonEvent() const
{
    return (this->_receiver.getLastButtonEvent());
}

Events::EditBox::eventEditBox Engine::getLastEditBoxEvent() const
{
    return (this->_receiver.getLastEditBoxEvent());
}

void Engine::drawAllImages()
{
    for (auto &element : this->_images)
        element.drawImage();
}

void Engine::addImage(std::string path)
{
    Image new_image(this->_driver);
    new_image.getImageFromAssets(path);
    this->_images.push_back(new_image);
}

void Engine::addButton(Events::Button::eventButton event, std::string content,
                       irr::core::rect<irr::s32> rect)
{
    std::wstring w_title = std::wstring(content.begin(), content.end());
    Button new_button(this->_env);
    this->_env->addButton(rect, 0, event, w_title.c_str());
    this->_buttons.push_back(new_button);
    this->listenToReceiver(event);
}

void Engine::addEditBox(Events::EditBox::eventEditBox event,
                        std::string content, irr::core::rect<irr::s32> rect)
{
    std::wstring w_title = std::wstring(content.begin(), content.end());
    Button new_button(this->_env);
    this->_env->addEditBox(w_title.c_str(), rect, true, 0, event);
    this->_buttons.push_back(new_button);
    this->listenToReceiver(event);
}

void Engine::clearLastEditBoxEvent()
{
    this->_receiver.clearLastEditBoxEvent();
}

void Engine::clearImages()
{
    this->_images.clear();
}

void Engine::clearButtons()
{
    this->_buttons.clear();
}

irr::scene::ISceneManager *Engine::getScene() const
{
    return (this->_scene);
}

void Engine::addPlayers(std::vector<std::vector<int>> &map)
{
    int nbPlayer = 0;

    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 3) {
                std::map<int, irr::scene::IAnimatedMeshSceneNode *>::iterator it = _players.begin();
                _players.insert(it, std::pair<int, irr::scene::IAnimatedMeshSceneNode *>(nbPlayer++, addAnimatedMesh("Assets/BomberBlack", i, j)));
            }
            if (map[i][j] == 6) {
                std::map<int, irr::scene::IAnimatedMeshSceneNode *>::iterator it = _players.begin();
                _players.insert(it, std::pair<int, irr::scene::IAnimatedMeshSceneNode *>(nbPlayer, addAnimatedMesh("Assets/BomberBlack", i, j)));
                nbPlayer += 1;
            }
        }
    }
}

irr::scene::IAnimatedMeshSceneNode *Engine::addAnimatedMesh(std::string path, int  i, int j)
{
    std::string _mesh_path = path + ".md3";
    std::string _texture_path = path + ".png";

    irr::scene::IAnimatedMesh *mesh = this->_scene->getMesh(_mesh_path.c_str());
    irr::scene::IAnimatedMeshSceneNode *node;
    if (!mesh)
        return nullptr;
    node = this->_scene->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setName(path.c_str());
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setFrameLoop(2, 40);
        node->setRotation(irr::core::vector3df(0, 180, 0));
        node->setAnimationSpeed(40);
        node->setScale(irr::core::vector3df(20, 30, 20));
        node->setPosition(irr::core::vector3df(i * 20, -10, j * 20));
        node->setMaterialTexture(
            0, this->_driver->getTexture(_texture_path.c_str()));
    }
    return node;
}

void Engine::applyTexture()
{
}

void Engine::drawScene()
{
    if (this->_scene != NULL)
        this->_scene->drawAll();
}

int Engine::changeAnimation(int actual, int change, irr::scene::IAnimatedMeshSceneNode* node)
{
    if (actual == change)
        return actual;
    else if (change == 0) {
        node->setFrameLoop(2, 40);
        return 0;
    }
    else if (change == 1) {
        node->setFrameLoop(42, 80);
        return 1;
    }
    return 0;
}

void Engine::movePlayer(std::vector<std::vector<int>> &map, KeyEnum key)
{
    int posx = 0;
    int posy = 0;
    int botnb = 1;

    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 3 || map[i][j] == 12 || map[i][j] == 13) {
                posx = i;
                posy = j;
            }
            if (map[i][j] == 6 || map[i][j] == 14) {
                _players[botnb]->setPosition(irr::core::vector3df(i * 20, -20, j * 20));
                botnb += 1;
            }
        }
    }
    if (key == KeyEnum::DOWN) {
        _actual = changeAnimation(_actual, 1, _players[0]);
        _players[0]->setRotation(irr::core::vector3df(0, 270, 0));
    } else if (key == KeyEnum::LEFT) {
        _actual = changeAnimation(_actual, 1, _players[0]);
        _players[0]->setRotation(irr::core::vector3df(0, 0, 0));
    } else if (key == KeyEnum::UP) {
        _actual = changeAnimation(_actual, 1, _players[0]);
        _players[0]->setRotation(irr::core::vector3df(0, 90, 0));
    } else if (key == KeyEnum::RIGHT) {
        _actual = changeAnimation(_actual, 1, _players[0]);
        _players[0]->setRotation(irr::core::vector3df(0, 180, 0));
    } else {
        _actual = changeAnimation(_actual, 0, _players[0]);
    }
    _players[0]->setPosition(irr::core::vector3df(posx * 20, -20, posy * 20));
}

KeyEnum Engine::getKey()
{
    if (_receiver.isKeyDown(irr::KEY_KEY_Z)) {
        return KeyEnum::UP;
    }
    if (_receiver.isKeyDown(irr::KEY_KEY_S)) {
        return KeyEnum::DOWN;
    }
    if (_receiver.isKeyDown(irr::KEY_KEY_D)) {
        return KeyEnum::RIGHT;
    }
    if (_receiver.isKeyDown(irr::KEY_KEY_Q)) {
        return KeyEnum::LEFT;
    }
    if(_receiver.isKeyDown(irr::KEY_SPACE)) {
        return KeyEnum::SPACE;
    }
    if(_receiver.isKeyDown(irr::KEY_RETURN)) {
        return KeyEnum::ENTER;
    }
    return KeyEnum::UNDEFINED;
}

void Engine::initMap(std::vector<std::vector<int>> map)
{
    irr::scene::ISceneNode* node;

    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            this->_nodes[i][j] = NULL;
            if (map[i][j] == 1) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/Wall.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if (map[i][j] == 2) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/Block.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
                this->_nodes[i][j]->setMaterialType(irr::video::EMT_SOLID);
            }
            if (map[i][j] == 4) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/TNT.jpg"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
                this->_nodes[i][j]->setMaterialType(irr::video::EMT_SOLID);
            }
            if (map[i][j] == 5 || map[i][j] == 7) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/Fire.jpg"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
                this->_nodes[i][j]->setMaterialType(irr::video::EMT_SOLID);
            }
            if (map[i][j] == 8) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/Speed.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
                this->_nodes[i][j]->setMaterialType(irr::video::EMT_SOLID);
            }
            if (map[i][j] == 9) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/Pass.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
                this->_nodes[i][j]->setMaterialType(irr::video::EMT_SOLID);
            }
            if (map[i][j] == 10) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/Power.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if (map[i][j] == 11) {
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/BombUp.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            node = this->_scene->addCubeSceneNode(20);
            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            node->setMaterialTexture(0, this->_driver->getTexture("Assets/Grass.jpg"));
            node->setPosition(irr::core::vector3df(20 * i, -20, j * 20));
        }
    }
}

void Engine::drawMap(std::vector<std::vector<int>> map)
{
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if ((map[i][j] == 0 && this->_last[i][j] != 0) || (map[i][j] == 3 && this->_last[i][j] != 3)) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = NULL;
            }
            if (map[i][j] == 1 && this->_last[i][j] != 1) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/Wall.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if (map[i][j] == 2 && this->_last[i][j] != 2) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/Block.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if ((map[i][j] == 4 && this->_last[i][j] != 4) || (map[i][j] == 13 && this->_last[i][j] != 13)) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/TNT.jpg"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if ((map[i][j] == 5 && this->_last[i][j] != 5) || (map[i][j] == 7 && this->_last[i][j] != 7)) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/Fire.jpg"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if (map[i][j] == 8 && this->_last[i][j] != 8) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/Speed.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if (map[i][j] == 9 && this->_last[i][j] != 9) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(0,
                                         this->_driver->getTexture("Assets/Pass.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if (map[i][j] == 10 && this->_last[i][j] != 10) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/Power.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
            if (map[i][j] == 11 && this->_last[i][j] != 11) {
                if (this->_nodes[i][j])
                    this->_nodes[i][j]->remove();
                this->_nodes[i][j] = this->_scene->addCubeSceneNode(20);
                this->_nodes[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                this->_nodes[i][j]->setMaterialTexture(
                    0, this->_driver->getTexture("Assets/BombUp.png"));
                this->_nodes[i][j]->setPosition(irr::core::vector3df(20 * i, 0, j * 20));
            }
        }
    }
}

void Engine::setLight()
{
    this->_scene->addLightSceneNode(0, irr::core::vector3df(-15, 5, -105),
                                    irr::video::SColorf(255, 255, 255));
    this->_scene->setAmbientLight(irr::video::SColor(0, 250, 250, 250));
}

void Engine::setCamera()
{
    this->_scene->addCameraSceneNode(0, irr::core::vector3df(186, 181, 173),
                                     irr::core::vector3df(38, -409, 173));
}

void Engine::startScene()
{
    this->_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
}

void Engine::addAndPlaySound(const std::string &name, const std::string &path)
{
    this->addSound(name, path);
    this->playSound(name);
}

void Engine::addSound(const std::string &name, const std::string &path)
{
    this->_sounds[name].addSound(path);
}

void Engine::playSound(const std::string &name)
{
    this->_sounds[name].playSound();
}

void Engine::stopSound(const std::string &name)
{
    this->_sounds[name].stopSound();
}
