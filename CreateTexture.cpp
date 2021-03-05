#include "CreateTexture.hpp"
#include "StandardTexture.hpp"
#include <MhLib/Media/Image/MhPNG.hpp>
#include <MhLib/Media/Image/MhJPEG.hpp>.hpp>

std::shared_ptr<Texture> createTexture(const MH33::Image::DecodeTarget &decodedImage)
{
	if(decodedImage.frames.size()) {
		const auto& frame = decodedImage.frames[0];
		switch (decodedImage.format) {
		case MH33::Image::Format::RGB8U:
			{
				std::shared_ptr<TextureRGB<uint8_t>> tex = std::shared_ptr<TextureRGB<uint8_t>>(new TextureRGB<uint8_t>(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA8U:
			{
				std::shared_ptr<TextureRGBA<uint8_t>> tex = std::shared_ptr<TextureRGBA<uint8_t>>(new TextureRGBA<uint8_t>(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		default:
			break;
		}
	}
	return nullptr;
}

std::shared_ptr<Texture> textureFromPNG(MH33::Io::Device &iodevice)
{
	MH33::Image::DecodeTarget decodeTarget;
	MH33::Image::PNG::decode(iodevice,decodeTarget);
	return createTexture(decodeTarget);
}

std::shared_ptr<Texture> textureFromJPEG(MH33::Io::Device &iodevice)
{
	MH33::Image::DecodeTarget decodeTarget;
	MH33::Image::JPEG::decode(iodevice,decodeTarget);
	return createTexture(decodeTarget);
}
