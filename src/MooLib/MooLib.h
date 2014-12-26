#pragma once

// macros
#include "Macros.h"

// general build configuration
#include "Configuration.h"

// native platform
// @TODO: wrap support for future platforms
#include "PlatformWin32.h"

// C Standard Library
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
//#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint> // C++11
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar> // C++11
#include <cwctype> // C++11
#include <chrono> // C++11

// C++ Standard Library
#include <algorithm>
#include <functional>
#include <iterator>
#include <locale>
#include <memory>
#include <stdexcept>
#include <tuple> // C++11
#include <utility>
#include <iterator>

// C++ Standard Library Containers
#include <array> // C++11
#include <bitset>
#include <deque>
#include <forward_list> // C++11
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map> // C++11
#include <unordered_set> // C++11
#include <vector>

// C++ Standard Library Strings
#include <string>

// C++ Standard Library IO/Streams
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <streambuf>

// C++ Standard Library Numerics
#include <complex>
#include <numeric>
#include <random> // C++11
#include <valarray>

// C++ Standard Library Language
#include <exception>
#include <limits>
#include <new>
#include <typeinfo>

// C++ Standard Library Threading
#include <thread> // C++11
#include <mutex> // C++11
#include <condition_variable> // C++11
#include <future> // C++11
#include <atomic> // C++11

// windows
#include <tchar.h>

// util
#include "Handle.h"
#include "SourceInfo.h"
#include "Threading.h"
#include "Logger.h"
#include "Assert_ML.h"
#include "FixedString.h"
#include "Tokenizer.h"
#include "FileSystem/File.h"
#include "ActiveObject.h"