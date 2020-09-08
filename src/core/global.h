#ifndef LIGHTPAD_GLOBAL_H
#define LIGHTPAD_GLOBAL_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#  define LP_OS_WINDOWS
#elif defined(__linux__) || defined(__linux)
#  define LP_OS_LINUX
#else
#  error "Unsupported platform"
#endif

#if defined(LP_OS_WINDOWS)
#  define LP_EXPORT __declspec(dllexport)
#  define LP_IMPORT __declspec(dllimport)
#elif defined(LP_OS_LINUX)
#  define LP_EXPORT __attribute__((visibility("default")))
#  define LP_IMPORT __attribute__((visibility("default")))
#else
#  define LP_EXPORT
#  define LP_IMPORT
#endif


#define LP_API extern "C" LP_EXPORT

#define interface struct


#endif // LIGHTPAD_GLOBAL_H
