#pragma once

#include "FileSystem.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>

namespace Freeking
{
	struct PakHeader
	{
		int id;
		int offset;
		int size;
	};

	struct PakFileItem
	{
		char name[56];
		int offset;
		int size;
	};

	class PakFileSystem : public IFileSystem
	{
	public:

		static std::unique_ptr<PakFileSystem> Create(const std::filesystem::path& path);

		PakFileSystem(const std::filesystem::path& path);
		~PakFileSystem();

		virtual bool FileExists(const std::string& filename) override;
		virtual std::vector<char> GetFileData(const std::string& filename) override;

	private:

		struct FileItem
		{
			int offset;
			int size;
		};

		static const int Id = 0x4B434150;

		std::ifstream _stream;
		std::unordered_map<std::string, FileItem> _fileItems;
	};
}
