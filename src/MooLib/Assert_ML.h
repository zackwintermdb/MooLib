#pragma once

#ifdef ML_MASTER
#	define ME_MASTER 1
#else
#	define ME_MASTER 0
#endif


#include "Assert_ME.h"


#define ML_BREAKPOINT ME_BREAKPOINT

#define ML_UNUSED ME_UNUSED
#define ML_UNUSED_IMPL ME_UNUSED_IMPL

#define ML_PP_PASS_ARGS ME_PP_PASS_ARGS
#define ML_PP_EXPAND_ARGS ME_PP_EXPAND_ARGS

#if ML_ASSERT_ENABLED
#	define ML_ASSERT_IMPL_VAR(variable, n)			.Variable(#variable, variable)
#	define ML_ASSERT_IMPL_VARS(...)					ML_PP_EXPAND_ARGS ML_PP_PASS_ARGS(ML_ASSERT_IMPL_VAR, __VA_ARGS__),\
														ML_BREAKPOINT)
#	define ML_ASSERT(condition, format, ...)		(condition) ? ML_UNUSED(true) : (ml::Assert(ML_SOURCE_INFO,\
														"Assertion \"" #condition "\" failed. " format, __VA_ARGS__)\
														ML_ASSERT_IMPL_VARS
#else
#	define ML_ASSERT(condition, format, ...)		ML_UNUSED(condition), ML_UNUSED(format), ML_UNUSED(__VA_ARGS__),\
														ML_UNUSED
#endif

#if ML_DEBUG
#	define ML_DBGLOG_IMPL_VAR(variable, n)			.Variable(#variable, variable)
#	define ML_DBGLOG_IMPL_VARS(...)					ML_PP_EXPAND_ARGS ML_PP_PASS_ARGS(ML_DBGLOG_IMPL_VAR, __VA_ARGS__))
#	define ML_DBGLOG(format, ...)		(ml::Assert(ML_SOURCE_INFO,\
	format, __VA_ARGS__)\
	ML_DBGLOG_IMPL_VARS
#else
#	define ML_DBGLOG(format, ...)		ML_UNUSED(format), ML_UNUSED(__VA_ARGS__),\
	ML_UNUSED
#endif

#	define ML_LOG_IMPL_VAR(variable, n)			.Variable(#variable, variable)
#	define ML_LOG_IMPL_VARS(...)					ML_PP_EXPAND_ARGS ML_PP_PASS_ARGS(ML_LOG_IMPL_VAR, __VA_ARGS__))
#	define ML_LOG(format, ...)		(ml::Assert(ML_SOURCE_INFO,\
	format, __VA_ARGS__)\
	ML_LOG_IMPL_VARS

namespace ml {

class Assert
{
private:
	const SourceInfo& source_info_;
	int indent_len_;


public:
	Assert(const SourceInfo& Source_Info, const char* Entry_Format, ...);

	Assert& Variable(const char* const Variable_Name, bool Value);
	Assert& Variable(const char* const Variable_Name, int8_t Value);
	Assert& Variable(const char* const Variable_Name, int16_t Value);
	Assert& Variable(const char* const Variable_Name, int32_t Value);
	Assert& Variable(const char* const Variable_Name, int64_t Value);
	Assert& Variable(const char* const Variable_Name, uint8_t Value);
	Assert& Variable(const char* const Variable_Name, uint16_t Value);
	Assert& Variable(const char* const Variable_Name, uint32_t Value);
	Assert& Variable(const char* const Variable_Name, uint64_t Value);
	Assert& Variable(const char* const Variable_Name, float Value);
	Assert& Variable(const char* const Variable_Name, double Value);
	Assert& Variable(const char* const Variable_Name, const char* const Value);
	Assert& Variable(const char* const Variable_Name, const void* const Value);

	template <typename T>
	Assert& Variable(const char* const Variable_Name, T* const Value)
	{
		Dispatch(this->source_info_, "Assert %s == 0x%08x (pointer)", Variable_Name, Value);
		return *this;
	}

	template <typename T>
	Assert& Variable(const char* const Variable_Name, const T* const Value)
	{
		Dispatch(this->source_info_, "Assert %s == 0x%08x (pointer)", Variable_Name, Value);
		return *this;
	}

	template <typename T>
	Assert& Variable(const char* const Variable_Name, const T& Value)
	{
		// empty, user must impl
		return *this;
	}


private:
	template <typename T>
	static void Dispatch(const SourceInfo& Source_Info, const char* Fmt, const char* const Variable_Name, const T Value)
	{
		std::array<char, 8192> buf;

		strcpy(buf.data(), "\t");

		sprintf(buf.data() + 1, Fmt, Variable_Name, Value);

		log::Write(buf.data());
	}


private:
	ML_NO_COPY(Assert);
	ML_NO_ASSIGN(Assert);
};

} // namespace ml