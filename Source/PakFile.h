#pragma once

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

	class PakFile
	{
	public:

		PakFile(const std::filesystem::path& path);
		~PakFile();

		std::vector<char> GetFileData(const std::string& filename);

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
