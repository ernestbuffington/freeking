#pragma once

#include <glad/glad.h>
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

	struct TextureSamplerSettings
	{
		TextureWrapMode wrap;
		TextureFilterMode filter;

		bool operator==(const TextureSamplerSettings& other) const
		{
			return (wrap == other.wrap && filter == other.filter);
		}

		std::size_t operator()(const TextureSamplerSettings& other) const
		{
			return ((std::hash<TextureWrapMode>()(other.wrap) ^ (std::hash<TextureFilterMode>()(other.filter) << 1)) >> 1);
		}
	};

	class TextureSampler;

	class TextureSamplerLibrary
	{
	public:

		const std::shared_ptr<TextureSampler>& Get(TextureSamplerSettings settings)
		{
			if (auto it = _samplers.find(settings); it != _samplers.end())
			{
				return it->second;
			}
			else
			{
				return _samplers.emplace(settings, std::make_shared<TextureSampler>(settings)).first->second;
			}
		}

	private:

		std::unordered_map<TextureSamplerSettings, std::shared_ptr<TextureSampler>, TextureSamplerSettings> _samplers;
	};

	class TextureSampler
	{
	public:

		static TextureSamplerLibrary Library;
		static std::shared_ptr<TextureSampler> GetDefault();

		TextureSampler(const TextureSamplerSettings& settings);
		~TextureSampler();

		void Bind(GLuint unit);

		inline GLuint GetHandle() const { return _handle;  }

	private:

		GLuint _handle;
	};
}
