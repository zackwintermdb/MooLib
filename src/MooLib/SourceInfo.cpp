#include "pch.h"
#include "SourceInfo.h"


namespace ml {

SourceInfo empty_src_info(invalid_str, invalid_int32, invalid_str, invalid_str);

const char* SourceInfo::GetShortFileName() const
{
	if (this->file_ == nullptr) {
		return this->file_;
	}

	int count = 0;
	const char* ptr = this->file_;
	while (*ptr != '\0') {
		if (*ptr == '\\') {
			++count;
		}
		++ptr;
	}

	ptr = this->file_;
	while (*ptr != '\0') {
		if (count <= 1) {
			break;
		}

		if (*ptr == '\\') {
			--count;
		}
		++ptr;
	}

	return ptr;
}

} // namespace ml