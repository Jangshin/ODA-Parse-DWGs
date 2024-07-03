/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2024, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2023 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
// GLES2 include

#ifndef ODTRGL2INCLUDE
#define ODTRGL2INCLUDE

#include "OdPlatformSettings.h"

// Includes for OpenGL ES 2.0
#ifdef EMCC
#include<GLES2/gl2.h>

#elif  __APPLE__

#include <TargetConditionals.h>

#if ((defined(TARGET_OS_IOS) && (TARGET_OS_IOS)) \
    || ((defined(TARGET_OS_IPHONE) && (TARGET_OS_IPHONE)) \
    || (defined(TARGET_IPHONE_SIMULATOR) && (TARGET_IPHONE_SIMULATOR)) \
    || (defined(TARGET_OS_SIMULATOR) && (TARGET_OS_SIMULATOR)))) \
    && !defined(TD_USING_GLU) && !defined(TD_OPEN_GLES_MISSING)
// iOS (device or simulator)
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
    #define OD_TRGL2_IOS
#elif (defined(TARGET_OS_OSX) && (TARGET_OS_OSX))
// MacOS, moved here from other desktop platforms since it is __APPLE__ block
    #include "compatibility/gles2_ext.h"
#else
#error "ERROR: Unsupported Apple platform (not iOS/iOS simulator/MacOS)"
#endif

#elif defined(ANDROID) || defined(TRGL2EMUL_ENABLED) || defined(EMCC)
#include <GLES2/gl2.h>
// Includes for EGL
#include <EGL/egl.h>
// EGL is available only since 9 Android platform, define this for platform 8 and earlier
//#define OD_TRGL2_NOEGL
#else // #elif Apple/Android

// Windows/Linux/Sun and etc. PC OS
#include "compatibility/gles2_ext.h"

#endif

#if defined(ANDROID) || defined(OD_TRGL2_IOS) || defined(EMCC)
#define OD_TRGL2_NATIVEES2
#endif

#endif // ODTRGL2INCLUDE
