/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Button
*/
#include <irrlicht.h>

#ifndef BUTTON_HPP_
#define BUTTON_HPP_
#include <iostream>
#include <vector>

class Button {
public:
    Button(irr::gui::IGUIEnvironment *);
    ~Button();
    void setButton(irr::gui::IGUIButton *);
    irr::gui::IGUIButton *getButton() const;

protected:
private:
    irr::gui::IGUIButton *_button;
    irr::gui::IGUIEnvironment *_env;
};

#endif /* !BUTTON_HPP_ */
