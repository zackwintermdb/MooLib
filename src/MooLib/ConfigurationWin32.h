#pragma once

#pragma warning(disable : 4514)
#pragma warning(disable : 4820)
#pragma warning(disable : 4275)
#pragma warning(disable : 4574)
#pragma warning(disable : 4710)
#pragma warning(disable : 4711)
#pragma warning(disable : 4481)


#if ML_DEBUG
#	define _HAS_ITERATOR_DEBUGGING 1
#	define _SECURE_SCL 1
#elif ML_RELEASE
#	define _HAS_ITERATOR_DEBUGGING 0
#	define _SECURE_SCL 0
#elif ML_SHIPPING
#	define _HAS_ITERATOR_DEBUGGING 0
#	define _SECURE_SCL 0
#endif
