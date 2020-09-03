#pragma once

#include "glapi.h"

namespace GLAbstract
{
	struct TexturePos
	{
		GLint x, y, z;
	};

	struct TextureInfo
	{
		GLenum target;
		GLsizei levels;
		GLenum internalFormat;
		TexturePos size;
	};

	class Texture
	{
	public:
		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;

		Texture(GLuint handle);
		Texture(const TextureInfo& info);
		~Texture();
		
		void Bind(GLuint unit = 0u);

		void Storage(GLint level, TexturePos offset, TexturePos size, GLenum format, GLenum type, void* pixels);

		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		inline const TextureInfo& GetTextureInfo() const
		{
			return m_Info;
		}

		inline GLuint GetHandle() const
		{
			return m_Handle;
		}
	private:
		TextureInfo m_Info;
		GLuint m_Handle;
	};
}