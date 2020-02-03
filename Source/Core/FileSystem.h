#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <memory>

namespace Freeking
{
	class IFileSystem
	{
	public:

		IFileSystem() {}
		virtual ~IFileSystem() {}

		virtual bool FileExists(const std::string& filename) = 0;
		virtual std::vector<char> GetFileData(const std::string& filename) = 0;
	};

	class FileSystem
	{
	public:

		FileSystem() = delete;
		~FileSystem() = delete;

		static void AddFileSystem(std::unique_ptr<IFileSystem> fileSystem);
		static bool FileExists(const std::string& filename);
		static std::vector<char> GetFileData(const std::string& filename);

	private:

		static std::vector<std::unique_ptr<IFileSystem>> _fileSystems;
	};
}
