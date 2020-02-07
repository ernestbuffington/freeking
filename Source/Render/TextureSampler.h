#pragma once

#include <glad/gl.h>
#include <unordered_map>
#include <memory>
#include <functional>

namespace Freeking
{
	enum class TextureWrapMode : int
	{
		Repeat,
		ClampEdge,
	};

	enum class TextureFilterMode : int
	{
		Linear,
		Nearest,
		LinearNoMip,
		NearestNoMip,
	};

	struct TextureSamplerInitializer
	{
		TextureWrapMode wrap;
		TextureFilterMode filter;

		bool operator==(const TextureSamplerInitializer& other) const
		{
			return (wrap == other.wrap && filter == other.filter);
		}

		std::size_t operator()(const TextureSamplerInitializer& other) const
		{
			return ((std::hash<TextureWrapMode>()(other.wrap) ^ (std::hash<TextureFilterMode>()(other.filter) << 1)) >> 1);
		}
	};

	class TextureSampler;

	class TextureSamplerLibrary
	{
	public:

		using TextureSamplerPtr = std::shared_ptr<TextureSampler>;

		const TextureSamplerPtr& Get(const TextureSamplerInitializer& settings);

	private:

		std::unordered_map<TextureSamplerInitializer, TextureSamplerPtr, TextureSamplerInitializer> _samplers;
	};

	class TextureSampler
	{
	public:

		static TextureSamplerLibrary Library;
		static std::shared_ptr<TextureSampler> GetDefault();

		TextureSampler(const TextureSamplerInitializer& settings);
		~TextureSampler();

		void Bind(GLuint unit);

		inline GLuint GetHandle() const { return _handle;  }

	private:

		GLuint _handle;
	};
}
