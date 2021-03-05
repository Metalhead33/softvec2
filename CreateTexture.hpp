#ifndef CREATETEXTURE_HPP
#define CREATETEXTURE_HPP
#include <memory>
#include "Texture.hpp"
#include <MhLib/Media/Image/MhDecodeTarget.hpp>
#include <MhLib/Io/MhIoDevice.hpp>

std::shared_ptr<Texture> createTexture(const MH33::Image::DecodeTarget& decodedImage);
std::shared_ptr<Texture> textureFromPNG(MH33::Io::Device& iodevice);
std::shared_ptr<Texture> textureFromJPEG(MH33::Io::Device& iodevice);

#endif // CREATETEXTURE_HPP
