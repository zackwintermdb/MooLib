#pragma once

namespace ml {

namespace FileSystem {
	enum class OpenMode : uint16_t {
		None = 0x0000,
		Read = 0x0001,
		Write = 0x0002,
		Append = 0x0004,
		Share = 0x0008,
		Create = 0x0010,
		RandomAccess = 0x0020
	};

	inline OpenMode operator | (OpenMode lhs, OpenMode rhs)
	{
		return (OpenMode)((uint16_t)lhs | (uint16_t)rhs);
	}

	inline bool operator & (OpenMode lhs, OpenMode rhs)
	{
		return ((uint16_t)lhs & (uint16_t)rhs) != 0;
	}

	inline OpenMode& operator |= (OpenMode& lhs, OpenMode rhs)
	{
		lhs = (OpenMode)((uint16_t)lhs | (uint16_t)rhs);
		return lhs;
	}

	enum SeekType {
		Current,
		Begin,
		End
	};
};  // namespace FileSystem
} // namespace ml