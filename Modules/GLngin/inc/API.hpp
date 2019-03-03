#pragma once

#ifndef GLNGIN_API_HPP
#define GLNGIN_API_HPP

#if defined (_WIN32)
#   define DLL_EXPORT __declspec (dllexport)
#   define DLL_IMPORT __declspec (dllimport)
#   define DLL_LOCAL
#elif defined (__linux__)
#   define DLL_EXPORT __attribute__ ((visibility("default")))
#   define DLL_IMPORT
#   define DLL_LOCAL __attribute__ ((visibility("hidden")))
#else
#error Unsupported platform!
#endif

#if defined (GLNGIN_DYNAMIC_COMPILE)
#   define GLNGIN_API DLL_EXPORT
#elif defined (GLNGIN_STATIC_COMPILE)
#   define GLNGIN_API
#else
#   define GLNGIN_API DLL_IMPORT
#endif

#endif  // #ifndef GLNGIN_API_HPP
