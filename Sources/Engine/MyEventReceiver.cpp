/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** MyEventReceiver
*/

#include "MyEventReceiver.hpp"

MyEventReceiver::MyEventReceiver()
{
    this->_last_button_event = Events::Button::eventButton::NONE;
    for (irr::u32 i = 0; i < irr::EKEY_CODE::KEY_KEY_CODES_COUNT; i++)
        KeyIsDown[i] = false;
    _isPressed = false;
}

bool MyEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        _isPressed = true;
        tmp[event.KeyInput.Key] = KeyIsDown[event.KeyInput.Key];
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    } else {
        _isPressed = false;
    }
    for (auto ptr = this->_buttons_events.begin();
         ptr < this->_buttons_events.end(); ptr++)
        if (event.EventType == irr::EET_GUI_EVENT) {
            irr::s32 id = event.GUIEvent.Caller->getID();
            if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                if (id == *ptr)
                    this->_last_button_event = *ptr;
            }
        }
    for (auto ptr = this->_editbox_events.begin();
         ptr < this->_editbox_events.end(); ptr++)
        if (event.EventType == irr::EET_GUI_EVENT) {
            irr::s32 id = event.GUIEvent.Caller->getID();
            if (event.GUIEvent.EventType == irr::gui::EGET_EDITBOX_ENTER) {
                if (id == *ptr)
                    this->_last_editbox_event = *ptr;
            }
        }
    return (false);
}

Events::Button::eventButton MyEventReceiver::getLastButtonEvent() const
{
    return (this->_last_button_event);
}

void MyEventReceiver::addButtonEvent(Events::Button::eventButton button)
{
    this->_buttons_events.push_back(button);
}

Events::EditBox::eventEditBox MyEventReceiver::getLastEditBoxEvent() const
{
    return (this->_last_editbox_event);
}

bool MyEventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

void MyEventReceiver::addEditBoxEvent(Events::EditBox::eventEditBox editbox)
{
    this->_editbox_events.push_back(editbox);
}

void MyEventReceiver::clearLastEditBoxEvent()
{
    this->_last_editbox_event = Events::EditBox::eventEditBox::NONE;
}
