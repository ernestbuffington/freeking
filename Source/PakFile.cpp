#include "PakFile.h"

namespace Freeking
{
	PakFile::PakFile(const std::filesystem::path& path)
	{
		_stream.open(path, std::ios::binary | std::ios::ate);

		PakHeader header;
		_stream.seekg(0);
		_stream.read((char*)&header, sizeof(header));

		if (header.id == Id)
		{
			int numFiles = header.size / sizeof(PakFileItem);
			std::vector<PakFileItem> fileItems(numFiles);

			_stream.seekg(header.offset);
			_stream.read((char*)fileItems.data(), header.size);

			_fileItems.reserve(numFiles);

			for (const PakFileItem& fileItem : fileItems)
			{
				_fileItems.emplace(
					std::string(fileItem.name),
					FileItem
					{ 
						fileItem.offset,
						fileItem.size
					});
			}
		}
		else
		{
			_stream.close();
		}
	}

	PakFile::~PakFile()
	{
		if (_stream.is_open())
		{
			_stream.close();
		}
	}

	std::vector<char> PakFile::GetFileData(const std::string& filename)
	{
		if (!_stream.is_open())
		{
			return {};
		}

		auto it = _fileItems.find(filename);
		if (it == _fileItems.end())
		{
			return {};
		}

		const auto& fileItem = it->second;
		std::vector<char> fileData(fileItem.size);
		_stream.seekg(fileItem.offset);
		_stream.read((char*)fileData.data(), fileItem.size);

		return fileData;
	}
}
