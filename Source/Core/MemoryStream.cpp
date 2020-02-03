#include "MemoryStream.h"

namespace Freeking
{
	MemoryStream::MemoryStream(const std::vector<uint8_t>& data)
	{
		_data = data;
		_position = _data.begin();
	}

	void MemoryStream::Read(uint8_t* dest, std::size_t length)
	{
		std::memcpy(dest, &(*_position), length);
		std::advance(_position, length);
	}

	void MemoryStream::Seek(std::size_t position, SeekMode mode)
	{
		switch (mode)
		{
		case SeekMode::Begin: _position = std::next(_data.begin(), position); break;
		case SeekMode::Current: std::advance(_position, position); break;
		case SeekMode::End: _position = std::next(_data.end(), -static_cast<int32_t>(position)); break;
		}
	}
}
