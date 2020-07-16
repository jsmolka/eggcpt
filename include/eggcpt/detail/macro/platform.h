#pragma once

#ifdef _WIN32
#define EGGCPT_PLATFORM_WINDOWS 1
#else
#define EGGCPT_PLATFORM_WINDOWS 0
#endif

#ifdef __linux__
#define EGGCPT_PLATFORM_LINUX 1
#else
#define EGGCPT_PLATFORM_LINUX 0
#endif

#ifdef __APPLE__
#define EGGCPT_PLATFORM_DARWIN 1
#else
#define EGGCPT_PLATFORM_DARWIN 0
#endif

#if !(EGGCPT_PLATFORM_WINDOWS || EGGCPT_PLATFORM_LINUX || EGGCPT_PLATFORM_DARWIN)
#error Unsupported platform
#endif