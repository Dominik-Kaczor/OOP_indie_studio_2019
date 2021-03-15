/*
** EPITECH PROJECT, 2020
** indiestudio
** File description:
** Image
*/

#include "Image.hpp"

Image::Image(irr::video::IVideoDriver *video_driver)
{
    this->_video_driver = video_driver;
    this->_image = NULL;
}

Image::~Image()
{
}

void Image::getImageFromAssets(std::string &path)
{
    this->_image = this->_video_driver->getTexture(path.c_str());
    this->_size = (irr::core::dimension2d<irr::s32>)_image->getSize();
    this->_pos0.X = 0;
    this->_pos0.Y = 0;
    this->_pos1.X = _size.Width;
    this->_pos1.Y = _size.Height;
    this->_rectangle.UpperLeftCorner = _pos0;
    this->_rectangle.LowerRightCorner = _pos1;
}

void Image::drawImage()
{
    this->_video_driver->draw2DImage(_image, _pos0, _rectangle, 0,
                                        irr::video::SColor(255, 255, 255, 255),
                                        true);
}

irr::video::ITexture *Image::getImage() const
{
    return (this->_image);
}
