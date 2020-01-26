#pragma once

#include "FileSystem.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

namespace Freeking
{
	template <typename T>
	class AssetLoader
	{
	public:

		AssetLoader() {}

		using AssetPtr = std::shared_ptr<T>;

		AssetLoader(const AssetLoader&) = delete;
		AssetLoader& operator=(const AssetLoader&) = delete;

		virtual AssetPtr Load(const std::string& name) const { return nullptr; }
		virtual bool CanLoadExtension(const std::string& extension) const { return false; };
	};

	template <typename T>
	class AssetLibrary
	{
	public:

		using AssetPtr = std::shared_ptr<T>;
		using AssetLoaderPtr = std::unique_ptr<AssetLoader<T>>;

		AssetLibrary(const AssetLibrary&) = delete;
		AssetLibrary& operator=(const AssetLibrary&) = delete;

		AssetLibrary() {}

		AssetPtr Get(const std::string& name)
		{
			if (name.empty())
			{
				return nullptr;
			}

			if (auto it = _dictionary.find(name); it != _dictionary.end())
			{
				return it->second;
			}
			else
			{
				if (!FileSystem::FileExists(name))
				{
					return nullptr;
				}

				auto extension = std::filesystem::path(name).extension();
				if (extension.empty())
				{
					return nullptr;
				}

				if (_loaders.empty())
				{
					UpdateLoaders();
				}

				for (const auto& loader : _loaders)
				{
					if (!loader->CanLoadExtension(extension.string()))
					{
						continue;
					}

					if (auto asset = loader->Load(name))
					{
						_dictionary.emplace(name, asset);

						return asset;
					}
				}

				return nullptr;
			}
		}

	protected:

		virtual void UpdateLoaders() {}

		template<class T2> void AddLoader()
		{
			_loaders.emplace_back(std::make_unique<T2>());
		}

	private:

		std::unordered_map<std::string, AssetPtr> _dictionary;
		std::vector<AssetLoaderPtr> _loaders;
	};
}
