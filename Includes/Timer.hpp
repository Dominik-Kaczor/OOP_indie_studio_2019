/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <irrlicht.h>

class Timer {
public:
    Timer();
    ~Timer() = default;
    void setThen(irr::u32);
    void setNow(irr::u32);
    void setFrameDeltaTime(irr::f32);
    irr::u32 getThen() const;
    irr::u32 getNow() const;
    irr::f32 getFrameDeltaTime() const;
    void reset();

protected:
private:
    irr::u32 _then;
    irr::u32 _now;
    irr::f32 _frameDeltaTime;
};

#endif /* !TIMER_HPP_ */
