#pragma once

#include <vector>

namespace Freeking
{
	enum class SeekMode
	{
		Begin = SEEK_SET,
		Current = SEEK_CUR,
		End = SEEK_END
	};

	class MemoryStream
	{
	public:

		MemoryStream(const std::vector<uint8_t>&);

		void Read(uint8_t*, std::size_t);

		template <typename T>
		T Read()
		{
			uint8_t* ptr = &(*_position);
			T value = *reinterpret_cast<T*>(ptr);
			std::advance(_position, sizeof(T));

			return value;
		}

		void Seek(std::size_t position, SeekMode mode);
		inline std::size_t Position() { return std::distance(_data.begin(), _position); }
		inline std::size_t Size() const { return _data.size(); }
		inline bool End() const { return _position == _data.end(); }

	protected:

		std::vector<uint8_t> _data;
		std::vector<uint8_t>::iterator _position;
	};
}
