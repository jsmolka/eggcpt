#pragma once

#ifdef NDEBUG
#  define EGGCPT_DEBUG   0
#  define EGGCPT_RELEASE 1
#else
#  define EGGCPT_DEBUG   1
#  define EGGCPT_RELEASE 0
#endif

#ifdef _MSC_VER
#define EGGCPT_CC_MSVC 1
#else
#define EGGCPT_CC_MSVC 0
#endif

#ifdef __clang__
#define EGGCPT_CC_CLANG 1
#else
#define EGGCPT_CC_CLANG 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define EGGCPT_CC_GCC 1
#else
#define EGGCPT_CC_GCC 0
#endif

#ifdef __EMSCRIPTEN__
#define EGGCPT_CC_EMSCRIPTEN 1
#else
#define EGGCPT_CC_EMSCRIPTEN 0
#endif

#ifdef __MINGW32__
#define EGGCPT_CC_MINGW 1
#else
#define EGGCPT_CC_MINGW 0
#endif

#ifdef _WIN32
#define EGGCPT_OS_WINDOWS 1
#else
#define EGGCPT_OS_WINDOWS 0
#endif

#ifdef __linux__
#define EGGCPT_OS_LINUX 1
#else
#define EGGCPT_OS_LINUX 0 
#endif

#ifdef __APPLE__
#define EGGCPT_OS_DARWIN 1
#else
#define EGGCPT_OS_DARWIN 0
#endif
