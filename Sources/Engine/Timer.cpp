/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Timer
*/

#include "Timer.hpp"

Timer::Timer()
{
    this->_then = 0;
    this->_now = 0;
    this->_frameDeltaTime = 0;
}

void Timer::setThen(irr::u32 time)
{
    this->_then = time;
}

void Timer::setNow(irr::u32 time)
{
    this->_now = time;
}

void Timer::setFrameDeltaTime(irr::f32 time)
{
    this->_frameDeltaTime = time;
}

irr::f32 Timer::getFrameDeltaTime() const
{
    return (this->_frameDeltaTime);
}

irr::u32 Timer::getThen() const
{
    return (this->_then);
}

irr::u32 Timer::getNow() const
{
    return (this->_now);
}

void Timer::reset()
{
    this->_then = this->_now;
}
