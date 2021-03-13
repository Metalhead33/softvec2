#include "CreateTexture.hpp"
#include "StandardTexture.hpp"
#include <MhLib/Media/Image/MhPNG.hpp>
#include <MhLib/Media/Image/MhJPEG.hpp>

std::shared_ptr<Texture> createTexture(const MH33::Image::DecodeTarget &decodedImage)
{
	if(decodedImage.frames.size()) {
		const auto& frame = decodedImage.frames[0];
		switch (decodedImage.format) {
		case MH33::Image::Format::R8U:
			{
				std::shared_ptr<TextureGreyscaleU8> tex = std::shared_ptr<TextureGreyscaleU8>(new TextureGreyscaleU8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB8U:
			{
				std::shared_ptr<TextureRgbU8> tex = std::shared_ptr<TextureRgbU8>(new TextureRgbU8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA8U:
			{
				std::shared_ptr<TextureRgbaU8> tex = std::shared_ptr<TextureRgbaU8>(new TextureRgbaU8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB8U:
			{
				std::shared_ptr<TextureArgbU8> tex = std::shared_ptr<TextureArgbU8>(new TextureArgbU8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR8U:
			{
				std::shared_ptr<TextureBgrU8> tex = std::shared_ptr<TextureBgrU8>(new TextureBgrU8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA8U:
			{
				std::shared_ptr<TextureBgraU8> tex = std::shared_ptr<TextureBgraU8>(new TextureBgraU8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::R8S:
			{
				std::shared_ptr<TextureGreyscaleS8> tex = std::shared_ptr<TextureGreyscaleS8>(new TextureGreyscaleS8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB8S:
			{
				std::shared_ptr<TextureRgbS8> tex = std::shared_ptr<TextureRgbS8>(new TextureRgbS8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA8S:
			{
				std::shared_ptr<TextureRgbaS8> tex = std::shared_ptr<TextureRgbaS8>(new TextureRgbaS8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB8S:
			{
				std::shared_ptr<TextureArgbS8> tex = std::shared_ptr<TextureArgbS8>(new TextureArgbS8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR8S:
			{
				std::shared_ptr<TextureBgrS8> tex = std::shared_ptr<TextureBgrS8>(new TextureBgrS8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA8S:
			{
				std::shared_ptr<TextureBgraS8> tex = std::shared_ptr<TextureBgraS8>(new TextureBgraS8(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::R16U:
			{
				std::shared_ptr<TextureGreyscaleU16> tex = std::shared_ptr<TextureGreyscaleU16>(new TextureGreyscaleU16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB16U:
			{
				std::shared_ptr<TextureRgbU16> tex = std::shared_ptr<TextureRgbU16>(new TextureRgbU16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA16U:
			{
				std::shared_ptr<TextureRgbaU16> tex = std::shared_ptr<TextureRgbaU16>(new TextureRgbaU16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB16U:
			{
				std::shared_ptr<TextureArgbU16> tex = std::shared_ptr<TextureArgbU16>(new TextureArgbU16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR16U:
			{
				std::shared_ptr<TextureBgrU16> tex = std::shared_ptr<TextureBgrU16>(new TextureBgrU16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA16U:
			{
				std::shared_ptr<TextureBgraU16> tex = std::shared_ptr<TextureBgraU16>(new TextureBgraU16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::R16S:
			{
				std::shared_ptr<TextureGreyscaleS16> tex = std::shared_ptr<TextureGreyscaleS16>(new TextureGreyscaleS16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB16S:
			{
				std::shared_ptr<TextureRgbS16> tex = std::shared_ptr<TextureRgbS16>(new TextureRgbS16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA16S:
			{
				std::shared_ptr<TextureRgbaS16> tex = std::shared_ptr<TextureRgbaS16>(new TextureRgbaS16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB16S:
			{
				std::shared_ptr<TextureArgbS16> tex = std::shared_ptr<TextureArgbS16>(new TextureArgbS16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR16S:
			{
				std::shared_ptr<TextureBgrS16> tex = std::shared_ptr<TextureBgrS16>(new TextureBgrS16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA16S:
			{
				std::shared_ptr<TextureBgraS16> tex = std::shared_ptr<TextureBgraS16>(new TextureBgraS16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::R32U:
			{
				std::shared_ptr<TextureGreyscaleU32> tex = std::shared_ptr<TextureGreyscaleU32>(new TextureGreyscaleU32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB32U:
			{
				std::shared_ptr<TextureRgbU32> tex = std::shared_ptr<TextureRgbU32>(new TextureRgbU32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA32U:
			{
				std::shared_ptr<TextureRgbaU32> tex = std::shared_ptr<TextureRgbaU32>(new TextureRgbaU32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB32U:
			{
				std::shared_ptr<TextureArgbU32> tex = std::shared_ptr<TextureArgbU32>(new TextureArgbU32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR32U:
			{
				std::shared_ptr<TextureBgrU32> tex = std::shared_ptr<TextureBgrU32>(new TextureBgrU32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA32U:
			{
				std::shared_ptr<TextureBgraU32> tex = std::shared_ptr<TextureBgraU32>(new TextureBgraU32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::R32S:
			{
				std::shared_ptr<TextureGreyscaleS32> tex = std::shared_ptr<TextureGreyscaleS32>(new TextureGreyscaleS32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB32S:
			{
				std::shared_ptr<TextureRgbS32> tex = std::shared_ptr<TextureRgbS32>(new TextureRgbS32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA32S:
			{
				std::shared_ptr<TextureRgbaS32> tex = std::shared_ptr<TextureRgbaS32>(new TextureRgbaS32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB32S:
			{
				std::shared_ptr<TextureArgbS32> tex = std::shared_ptr<TextureArgbS32>(new TextureArgbS32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR32S:
			{
				std::shared_ptr<TextureBgrS32> tex = std::shared_ptr<TextureBgrS32>(new TextureBgrS32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA32S:
			{
				std::shared_ptr<TextureBgraS32> tex = std::shared_ptr<TextureBgraS32>(new TextureBgraS32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::R16F:
			{
				std::shared_ptr<TextureGreyscaleF16> tex = std::shared_ptr<TextureGreyscaleF16>(new TextureGreyscaleF16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB16F:
			{
				std::shared_ptr<TextureRgbF16> tex = std::shared_ptr<TextureRgbF16>(new TextureRgbF16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA16F:
			{
				std::shared_ptr<TextureRgbaF16> tex = std::shared_ptr<TextureRgbaF16>(new TextureRgbaF16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB16F:
			{
				std::shared_ptr<TextureArgbF16> tex = std::shared_ptr<TextureArgbF16>(new TextureArgbF16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR16F:
			{
				std::shared_ptr<TextureBgrF16> tex = std::shared_ptr<TextureBgrF16>(new TextureBgrF16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA16F:
			{
				std::shared_ptr<TextureBgraF16> tex = std::shared_ptr<TextureBgraF16>(new TextureBgraF16(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::R32F:
			{
				std::shared_ptr<TextureGreyscaleF32> tex = std::shared_ptr<TextureGreyscaleF32>(new TextureGreyscaleF32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGB32F:
			{
				std::shared_ptr<TextureRgbF32> tex = std::shared_ptr<TextureRgbF32>(new TextureRgbF32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::RGBA32F:
			{
				std::shared_ptr<TextureRgbaF32> tex = std::shared_ptr<TextureRgbaF32>(new TextureRgbaF32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::ARGB32F:
			{
				std::shared_ptr<TextureArgbF32> tex = std::shared_ptr<TextureArgbF32>(new TextureArgbF32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGR32F:
			{
				std::shared_ptr<TextureBgrF32> tex = std::shared_ptr<TextureBgrF32>(new TextureBgrF32(frame.width,frame.height));
				memcpy(tex->getPixels(),frame.imageData.data(),frame.imageData.size());
				return tex;
			}
		case MH33::Image::Format::BGRA32F:
			{
				std::shared_ptr<TextureBgraF32> tex = std::shared_ptr<TextureBgraF32>(new TextureBgraF32(frame.width,frame.height));
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
