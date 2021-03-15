/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(irr::gui::IGUIEnvironment *env)
{
    this->_env = env;
}

Button::~Button()
{
}

void Button::setButton(irr::gui::IGUIButton *button)
{
    this->_button = button;
}

irr::gui::IGUIButton *Button::getButton() const
{
    return (this->_button);
}
