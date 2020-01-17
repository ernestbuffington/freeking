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

	class PakFile : public IFileSystem
	{
	public:

		static std::unique_ptr<PakFile> Create(const std::filesystem::path& path);

		PakFile(const std::filesystem::path& path);
		~PakFile();

		virtual bool FileExists(const std::string& filename) override;
		virtual std::vector<char> GetFileData(const std::string& filename) override;

	protected:


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
