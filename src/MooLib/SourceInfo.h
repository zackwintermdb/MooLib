#pragma once

namespace ml {

struct SourceInfo;
extern SourceInfo empty_src_info;

struct SourceInfo
{
	inline SourceInfo(const char* const File, const uint32_t Line, const char* const Function, const char* const Function_Signature)
		: file_(File), line_(Line), function_(Function), function_signature_(Function_Signature)
	{
	}

	inline int Format(char* buffer) const
	{
		if (this == &empty_src_info) {
			buffer[0] = '\0';
			return 0;
		}

		return sprintf(buffer, "(%s in %s:%d)", 
			this->function_, GetShortFileName(), this->line_);
	}

	// get file name & its immediate directory
	const char* GetShortFileName() const;


	const char* const file_;
	const uint32_t line_;
	const char* const function_;
	const char* const function_signature_;

private:
	ML_NO_COPY(SourceInfo);
	ML_NO_ASSIGN(SourceInfo);
};
} // namespace ml