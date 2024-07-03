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
//   Open Design Alliance Copyright (C) 2002-2024 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////


#include "TD_PackPush.h"

#ifndef __OdString_Hasher_H__
#define __OdString_Hasher_H__

template<int sizeof_size_t = sizeof(size_t)>
struct OdString_Hasher {
  size_t operator()(const OdString& key) const; // "unresolved external symbol" means: Unsupported hash size: sizeof(size_t) != 4 && sizeof(size_t) != 8
};

/** \details
    This class implements 32-bit hash function for OdString objects in the ODA Platform.

    <group Other_Classes>
*/
template<>
struct OdString_Hasher<4> {
  size_t operator()(const OdString& key) const {
    OdUInt32 h = 0, g;
    const OdChar* pos = key.c_str();

    while(*pos != 0) {
      h = (h << 4) + *pos++;
      if((g = (h & 0xf00000000)) != 0)
        h ^= g >> 24;
      h &= ~g;
    }
    return h;
  }
};

/** \details
    This class implements 64-bit hash function for OdString objects in the ODA Platform.

    <group Other_Classes>
*/
template<>
struct OdString_Hasher<8> {
  size_t operator()(const OdString& key) const {
    OdUInt64 h = 0, g;
    const OdChar* pos = key.c_str();

    while(*pos != 0) {
      h = (h << 4) + *pos++;
      if((g = (h & 0xf000000000000000)) != 0)
        h ^= g >> 56;
      h &= ~g;
    }
    return static_cast<size_t>(h);
  }
};

//////////////////////////////////////////////////////////////////////////

#include "TD_PackPop.h"

#endif // #ifndef __OdString_Hasher_H__


