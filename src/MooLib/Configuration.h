#pragma once

#if ML_DEBUG
#	if ML_RELEASE
#		error [MooLib] Build configuration mismatch: ML_DEBUG & ML_RELEASE set!
#	elif ML_SHIPPING
#		error [MooLib] Build configuration mismatch: ML_DEBUG & ML_SHIPPING set!
#	endif
#elif ML_RELEASE
#	if ML_DEBUG
#		error [MooLib] Build configuration mismatch: ML_RELEASE & ML_DEBUG set!
#	elif ML_SHIPPING
#		error [MooLib] Build configuration mismatch: ML_RELEASE & ML_SHIPPING set!
#	endif
#elif ML_SHIPPING
#	if ML_DEBUG
#		error [MooLib] Build configuration mismatch: ML_SHIPPING & ML_DEBUG set!
#	elif ML_RELEASE
#		error [MooLib] Build configuration mismatch: ML_SHIPPING & ML_RELEASE set!
#	endif
#else
#	error [MooLib] Unknown build configuration!
#endif

#ifdef _WIN32
#	define ML_PLATFORM win32
#	define ML_PLATFORM_WIN32 1
#	include "ConfigurationWin32.h"
#else
#	error [MooLib] Unsupported platform!
#endif

#if ML_DEBUG
#	define ML_ASSERT_ENABLED 1
#elif ML_RELEASE
#	define ML_ASSERT_ENABLED 0
#elif ML_SHIPPING
#	define ML_ASSERT_ENABLED 0
#endif 