#include "GLAbstract/Texture.h"

#include <exception>
#include <stdexcept>

namespace GLAbstract
{
	Texture::Texture(GLuint handle)
		: m_Handle(handle)
	{
	}

	Texture::Texture(const TextureInfo& info)
		: m_Info(info)
	{
		glCreateTextures(info.target, 1, &m_Handle);

		switch (info.target)
		{
			case GL_TEXTURE_1D:
				glTextureStorage1D(m_Handle, info.levels, info.internalFormat, info.size.x);
				break;
			case GL_TEXTURE_1D_ARRAY:
				glTextureStorage2D(m_Handle, info.levels, info.internalFormat, info.size.x, info.size.y);
				break;
			case GL_TEXTURE_2D:
				glTextureStorage2D(m_Handle, info.levels, info.internalFormat, info.size.x, info.size.y);
				break;
			case GL_TEXTURE_2D_ARRAY:
				glTextureStorage3D(m_Handle, info.levels, info.internalFormat, info.size.x, info.size.y, info.size.z);
				break;
			case GL_TEXTURE_3D:
				glTextureStorage3D(m_Handle, info.levels, info.internalFormat, info.size.x, info.size.y, info.size.z);
				break;
			default:
				throw std::runtime_error("Unsupported texture target");
				break;
		}

		glTextureParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_Handle);
		m_Handle = 0;
	}

	void Texture::Bind(GLuint unit)
	{
		glBindTextureUnit(unit, m_Handle);
	}

	void Texture::Storage(GLint level, TexturePos offset, TexturePos size, GLenum format, GLenum type, void* pixels)
	{
		switch (m_Info.target)
		{
			case GL_TEXTURE_1D:
				glTextureSubImage1D(m_Handle, level, offset.x, size.x, format, type, pixels);
				break;
			case GL_TEXTURE_1D_ARRAY:
				glTextureSubImage2D(m_Handle, level, offset.x, offset.y, size.x, size.y, format, type, pixels);
				break;
			case GL_TEXTURE_2D:
				glTextureSubImage2D(m_Handle, level, offset.x, offset.y, size.x, size.y, format, type, pixels);
				break;
			case GL_TEXTURE_2D_ARRAY:
				glTextureSubImage3D(m_Handle, level, offset.x, offset.y, offset.z, size.x, size.y, size.z, format, type, pixels);
				break;
			case GL_TEXTURE_3D:
				glTextureSubImage3D(m_Handle, level, offset.x, offset.y, offset.z, size.x, size.y, size.z, format, type, pixels);
				break;
			default:
				throw std::runtime_error("Unsupported texture target");
				break;
		}
	}

	Texture::Texture(Texture&& other) noexcept
	{
		m_Info = other.m_Info;
		m_Handle = other.m_Handle;

		other.m_Handle = 0;
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		Texture::~Texture();
		m_Info = other.m_Info;
		m_Handle = other.m_Handle;

		other.m_Handle = 0;

		return *this;
	}

}