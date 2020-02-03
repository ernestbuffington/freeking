#include "FileSystem.h"
#include <filesystem>
#include <fstream>

namespace Freeking
{
	std::vector<std::unique_ptr<IFileSystem>> FileSystem::_fileSystems = {};

	void FileSystem::AddFileSystem(std::unique_ptr<IFileSystem> fileSystem)
	{
		if (fileSystem)
		{
			_fileSystems.push_back(std::move(fileSystem));
		}
	}

	bool FileSystem::FileExists(const std::string& filename)
	{
		for (const auto& fileSystem : _fileSystems)
		{
			if (fileSystem->FileExists(filename))
			{
				return true;
			}
		}

		return false;
	}

	std::vector<char> FileSystem::GetFileData(const std::string& filename)
	{
		for (const auto& fileSystem : _fileSystems)
		{
			if (fileSystem->FileExists(filename))
			{
				return fileSystem->GetFileData(filename);
			}
		}

		return {};
	}
}
