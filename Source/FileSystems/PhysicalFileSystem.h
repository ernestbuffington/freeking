#pragma once

#include "FileSystem.h"
#include <filesystem>

namespace Freeking
{
	class PhysicalFileSystem : public IFileSystem
	{
	public:

		static std::unique_ptr<PhysicalFileSystem> Create(const std::filesystem::path& path);

		PhysicalFileSystem(const std::filesystem::path& path);

		virtual bool FileExists(const std::string& filename) override;
		virtual std::vector<char> GetFileData(const std::string& filename) override;

	private:

		std::filesystem::path _path;
	};
}
