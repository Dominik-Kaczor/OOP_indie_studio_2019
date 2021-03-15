/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** MyEventReceiver
*/

#ifndef MyEventReceiver_HPP_
#define MyEventReceiver_HPP_
#include <irrlicht.h>
#include <vector>

namespace Events {
    namespace Button {
        enum eventButton {
            NONE = 0,
            GUI_PLAY_BUTTON,
            GUI_QUIT_BUTTON,
            GUI_SETTINGS_BUTTON,
            GUI_SETTINGS_GO_BACK,
            GUI_LOAD_BUTTON,
        };
    };
    namespace EditBox {
        enum eventEditBox {
            NONE = 0,
            EDIT_USERNAME,
        };
    };
}; // namespace Events

class MyEventReceiver : public irr::IEventReceiver {
public:
    MyEventReceiver();
    ~MyEventReceiver() = default;
    bool OnEvent(const irr::SEvent &event);
    void addButtonEvent(Events::Button::eventButton button);
    Events::Button::eventButton getLastButtonEvent() const;
    bool isKeyDown(irr::EKEY_CODE keyCode) const;
    void addEditBoxEvent(Events::EditBox::eventEditBox editbox);
    Events::EditBox::eventEditBox getLastEditBoxEvent() const;
    void clearLastEditBoxEvent();
    bool _isPressed;

private:
    std::vector<Events::Button::eventButton> _buttons_events;
    std::vector<Events::EditBox::eventEditBox> _editbox_events;
    Events::Button::eventButton _last_button_event;
    Events::EditBox::eventEditBox _last_editbox_event;
    bool KeyIsDown[irr::EKEY_CODE::KEY_KEY_CODES_COUNT];
    bool tmp[irr::EKEY_CODE::KEY_KEY_CODES_COUNT];
};

#endif /* !MyEventReceiver_HPP_ */
