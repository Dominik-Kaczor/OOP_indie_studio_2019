/*
** EPITECH PROJECT, 2020
** projets [SSH: 192.168.152.128]
** File description:
** main
*/

#include <irrlicht/irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MyEventReceiver : public IEventReceiver
{
    public:
        // This is the one method that we have to implement
        virtual bool OnEvent(const SEvent& event)
        {
            // Remember whether each key is down or up
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

            return false;
        }

        // This is used to check whether a key is being held down
        virtual bool IsKeyDown(EKEY_CODE keyCode) const
        {
            return KeyIsDown[keyCode];
        }
        
        MyEventReceiver()
        {
            for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                KeyIsDown[i] = false;
        }

    private:
        // We use this array to store the current state of each key
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int change_anim(int actual, int change, IAnimatedMeshSceneNode* node)
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
}

int main(int argc, char const *argv[])
{
    MyEventReceiver receiver;
    int actual = 0;

    IrrlichtDevice *device =
        createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
            false, false, false, &receiver);

    if (!device)
        return 1;
    
    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<s32>(10,10,260,22), true);
    
    IAnimatedMesh* mesh = smgr->getMesh("BomberBlack.md3");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
    
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);

        node->setFrameLoop(2, 40);
        node->setAnimationSpeed(40);
        //node->setMD2Animation(scene::EMAT_STAND);
        node->setScale(vector3df(10, 10, 10));
        node->setMaterialTexture( 0, driver->getTexture("black.png") );
    }

    smgr->addCameraSceneNode(0, vector3df(0,100,-10), vector3df(0,5,0));

    // In order to do framerate independent movement, we have to know
    // how long it was since the last frame
    u32 then = device->getTimer()->getTime();

    // This is the movemen speed in units per second.
    const f32 MOVEMENT_SPEED = 20.f;

    while(device->run()) {
        
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;
        core::vector3df nodePosition = node->getPosition();
        core::vector3df nodeRotation = node->getRotation();

        if(receiver.IsKeyDown(irr::KEY_KEY_Z)) {
            actual = change_anim(actual, 1, node);
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
            nodeRotation.Y = 180;
        }
        else if(receiver.IsKeyDown(irr::KEY_KEY_S)) {
            actual = change_anim(actual, 1, node);
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
            nodeRotation.Y = 0;
        }
        else if(receiver.IsKeyDown(irr::KEY_KEY_Q)) {
            actual = change_anim(actual, 1, node);
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
            nodeRotation.Y = 90;
        }
        else if(receiver.IsKeyDown(irr::KEY_KEY_D)) {
            actual = change_anim(actual, 1, node);
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
            nodeRotation.Y = 270;
        }
        else
            actual = change_anim(actual, 0, node);
        node->setPosition(nodePosition);
        node->setRotation(nodeRotation);

        driver->beginScene(true, true, SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();
    return 0;
}
