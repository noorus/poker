#pragma once

#include "TargetVer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef _DEBUG
//# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
#endif
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <eh.h>
#include <intrin.h>

// STL Headers
#include <exception>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <regex>
#include <stack>

// Boost Headers
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/random.hpp>
#include <boost/tokenizer.hpp>
#include <boost/variant.hpp>