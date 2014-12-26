#pragma once

// compiler macros
#define ML_PRAGMA(Pramga)							__pragma(Pramga)
#define ML_PUSH_WARNING_LEVEL(Level)				ML_PRAGMA(warning(push, Level))
#define ML_POP_WARNING_LEVEL						ML_PRAGMA(warning(pop))


// class macros
#define ML_NO_CREATE(Class_Name)					private: Class_Name()
#define ML_NO_COPY(Class_Name)						private: Class_Name(const Class_Name&)
#define ML_NO_ASSIGN(Class_Name)					private: Class_Name& operator=(const Class_Name&)


// invalid macros
#define invalid_int8								((int8_t)-1)
#define invalid_int16								((int16_t)-1)
#define invalid_int32								((int32_t)-1)
#define invalid_uint8								((uint8_t)-1)
#define invalid_uint16								((uint16_t)-1)
#define invalid_uint32								((uint32_t)-1)
#define invalid_str									"{INVALID}"


// source info
#if ML_DEBUG
#	define ML_SOURCE_INFO							ml::SourceInfo(__FILE__, __LINE__, __FUNCTION__, __FUNCSIG__)
#else
#	define ML_SOURCE_INFO							ml::empty_src_info
#endif


#define ML_STRINGIZE_HELPER(x)   #x
#define ML_STRINGIZE(x)  ML_STRINGIZE_HELPER(x)