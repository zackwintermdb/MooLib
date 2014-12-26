#include "pch.h"
#include "Assert.h"

namespace ml {

Assert::Assert(const SourceInfo& Source_Info, const char* Entry_Format, ...)
	: source_info_(Source_Info)
{
	std::array<char, 8192> buf;
	int len = 0;

	va_list args;
	va_start(args, Entry_Format);

	// @TODO: use portable vsprintf_s
	if (vsprintf_s(buf.data() + len, buf.size() - len, Entry_Format, args) == -1) {
		strcpy(buf.data() + len, "Invalid assert string format >> ");
		len += 32;
		strcpy(buf.data() + len, Entry_Format);
	}

	va_end(args);

	len = strlen(buf.data());

	if (Source_Info.line_ != -1) {
		buf[len] = ' ';
		++len;
	}

	Source_Info.Format(buf.data() + len);
	log::Write(buf.data());
}

Assert& Assert::Variable(const char* const Variable_Name, bool Value)
{
	Dispatch(this->source_info_, "Variable %s = %s (bool)", Variable_Name, Value ? "true" : "false");
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, int8_t Value)
{
	Dispatch(this->source_info_, "Variable %s = %d (int8)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, int16_t Value)
{
	Dispatch(this->source_info_, "Variable %s = %d (int16)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, int32_t Value)
{
	Dispatch(this->source_info_, "Variable %s = %d (int32)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, int64_t Value)
{
	// @TODO: add portable int64 parsing
	Dispatch(this->source_info_, "Variable %s = %I64d (int64)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, uint8_t Value)
{
	Dispatch(this->source_info_, "Variable %s = %u (uint8)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, uint16_t Value)
{
	Dispatch(this->source_info_, "Variable %s = %u (uint16)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, uint32_t Value)
{
	Dispatch(this->source_info_, "Variable %s = %u (uint32)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, uint64_t Value)
{
	// @TODO: add portable uint64 parsing
	Dispatch(this->source_info_, "Variable %s = %I64u (uint64)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, float Value)
{
	Dispatch(this->source_info_, "Variable %s = %1.4f (float)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, double Value)
{
	Dispatch(this->source_info_, "Variable %s = %1.4f (double)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, const char* const Value)
{
	Dispatch(this->source_info_, "Variable %s = %s (string)", Variable_Name, Value);
	return *this;
}


Assert& Assert::Variable(const char* const Variable_Name, const void* const Value)
{
	Dispatch(this->source_info_, "Variable %s = %p (pointer)", Variable_Name, Value);
	return *this;
}
} // namespace ml