#include "PhysicalFileSystem.h"
#include <fstream>

namespace Freeking
{
	std::unique_ptr<PhysicalFileSystem> PhysicalFileSystem::Create(const std::filesystem::path& path)
	{
		return std::make_unique<PhysicalFileSystem>(path);
	}

	PhysicalFileSystem::PhysicalFileSystem(const std::filesystem::path& path) :
		_path(path)
	{
	}

	bool PhysicalFileSystem::FileExists(const std::string& filename)
	{
		return std::filesystem::exists(_path / filename);
	}

	std::vector<char> PhysicalFileSystem::GetFileData(const std::string& filename)
	{
		auto filepath = _path / filename;
		if (!std::filesystem::exists(_path / filename))
		{
			return {};
		}

		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
		auto fileSize = std::filesystem::file_size(filepath);

		if (fileSize == 0)
		{
			return {};
		}

		std::vector<char> buffer(fileSize);
		stream.seekg(0);
		stream.read((char*)buffer.data(), buffer.size());

		return buffer;
	}
}
