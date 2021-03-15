/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_
#include <irrlicht.h>
#include <iostream>

class Image {
public:
    Image(irr::video::IVideoDriver *);
    ~Image();
    void getImageFromAssets(std::string &path);
    irr::video::ITexture *getImage() const;
    void drawImage();

protected:
private:
    irr::video::IVideoDriver *_video_driver;
    irr::video::ITexture *_image;
    irr::core::dimension2d<irr::s32> _size;
    irr::core::position2d<irr::s32> _pos0;
    irr::core::position2d<irr::s32> _pos1;
    irr::core::rect<irr::s32> _rectangle;
};

#endif /* !IMAGE_HPP_ */
