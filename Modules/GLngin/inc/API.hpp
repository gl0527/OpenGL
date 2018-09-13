#pragma once

#ifndef EXPORT_HPP
#define EXPORT_HPP

#if defined (GLNGIN_DLL_CONFIG)
#   if defined (_WIN32)
#       if defined (GLNGIN_DLL_EXPORT)
#           define GLNGIN_API __declspec (dllexport)
#       else
#           define GLNGIN_API
#       endif
#       define USE_GLNGIN_API __declspec (dllimport)
#   else
#       if defined (GLNGIN_DLL_EXPORT)
#           define GLNGIN_API __attribute__ ((visibility ("default")))
#       else
#           define GLNGIN_API __attribute__ ((visibility ("hidden")))
#       endif
#       define USE_GLNGIN_API
#   endif
#else
#define GLNGIN_API
#define USE_GLNGIN_API
#endif

#endif  // #ifndef EXPORT_HPP
