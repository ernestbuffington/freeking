#pragma once

#include "FileSystem.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <stack>
#include <algorithm>

namespace Freeking
{
	class PathStack
	{
	public:

		PathStack() = delete;
		PathStack(const std::filesystem::path& path) { _paths.push(path.parent_path()); }
		~PathStack() { _paths.pop(); }

		static std::filesystem::path Top() { return _paths.empty() ? "" : _paths.top(); }

	private:

		static std::stack<std::filesystem::path> _paths;
	};

	template <typename T>
	class AssetLoader
	{
	public:

		AssetLoader() {}
		virtual ~AssetLoader() {}

		using AssetPtr = std::shared_ptr<T>;

		AssetLoader(const AssetLoader&) = delete;
		AssetLoader& operator=(const AssetLoader&) = delete;

		virtual AssetPtr Load(const std::string&) const { return nullptr; }
		virtual bool CanLoadExtension(const std::string&) const { return false; };
	};

	template <typename T>
	class AssetLibrary
	{
	public:

		using AssetPtr = std::shared_ptr<T>;
		using AssetLoaderPtr = std::unique_ptr<AssetLoader<T>>;

		AssetLibrary() {}
		virtual ~AssetLibrary() {}

		AssetLibrary(const AssetLibrary&) = delete;
		AssetLibrary& operator=(const AssetLibrary&) = delete;

		AssetPtr Get(const std::string& name)
		{
			if (name.empty())
			{
				return nullptr;
			}

			if (auto it = _specialAssets.find(name); it != _specialAssets.end())
			{
				return it->second;
			}

			auto absolutePath = PathStack::Top() / name;
			auto absoluteName = absolutePath.string();
			std::replace(absoluteName.begin(), absoluteName.end(), '\\', '/');

			if (auto it = _pathAssets.find(absoluteName); it != _pathAssets.end())
			{
				return it->second;
			}
			else
			{
				if (!FileSystem::FileExists(absoluteName))
				{
					return nullptr;
				}

				auto extension = std::filesystem::path(absoluteName).extension();
				if (extension.empty())
				{
					return nullptr;
				}

				if (_loaders.empty())
				{
					UpdateLoaders();
				}

				PathStack ps(absolutePath);

				for (const auto& loader : _loaders)
				{
					if (!loader->CanLoadExtension(extension.string()))
					{
						continue;
					}

					if (auto asset = loader->Load(absoluteName))
					{
						_pathAssets.emplace(absoluteName, asset);

						return asset;
					}
				}

				return nullptr;
			}
		}

		void SetSpecialNamed(const std::string& name, AssetPtr asset)
		{
			_specialAssets.emplace(name, asset);
		}

		inline const std::unordered_map<std::string, AssetPtr>& GetPathAssets() const { return _pathAssets; }
		inline const std::unordered_map<std::string, AssetPtr>& GetSpecialAssets() const { return _specialAssets; }

	protected:

		virtual void UpdateLoaders() {}

		template<class T2> void AddLoader()
		{
			_loaders.emplace_back(std::make_unique<T2>());
		}

	private:

		std::unordered_map<std::string, AssetPtr> _pathAssets;
		std::unordered_map<std::string, AssetPtr> _specialAssets;
		std::vector<AssetLoaderPtr> _loaders;
	};
}
