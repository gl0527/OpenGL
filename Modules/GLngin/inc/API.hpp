#pragma once

#ifndef GLNGIN_API_HPP
#define GLNGIN_API_HPP

#if defined (_WIN32)
#   if defined (GLNGIN_DYNAMIC_COMPILE)
#       define GLNGIN_API __declspec (dllexport)
#   elif defined (GLNGIN_STATIC_COMPILE)
#       define GLNGIN_API
#   else
#       define GLNGIN_API __declspec (dllimport)
#   endif
#else
#       define GLNGIN_API
#endif

#endif  // #ifndef GLNGIN_API_HPP
