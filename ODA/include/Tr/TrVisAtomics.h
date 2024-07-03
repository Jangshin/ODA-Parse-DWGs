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
// Wrappers for atomic operations onto 16-bit integers

#ifndef ODTRVIS16BITATOMICOPS
#define ODTRVIS16BITATOMICOPS

#include "OdMutex.h"

#include "TD_PackPush.h"

namespace OdTrVisAtomics
{
#ifndef ARGSUSED
#define ARGSUSED(x)
#endif

  // 32-bit atomic operations

  // Increments incVal and returns incremented result value.
  inline OdUInt32 interlockedIncrement32(OdUInt32 &incVal)
  {
#ifndef TD_SINGLE_THREAD
    return (OdUInt32)::OdInterlockedIncrement(reinterpret_cast<volatile int*>(&incVal));
#else // TD_SINGLE_THREAD
    return ++incVal;
#endif // TD_SINGLE_THREAD
  }
  // Decrements decVal and returns decremented result value.
  inline OdUInt32 interlockedDecrement32(OdUInt32 &decVal)
  {
#ifndef TD_SINGLE_THREAD
    return (OdUInt32)::OdInterlockedDecrement(reinterpret_cast<volatile int*>(&decVal));
#else // TD_SINGLE_THREAD
    return ++decVal;
#endif // TD_SINGLE_THREAD
  }
  // Post-increment
  inline OdUInt32 interlockedPostIncrement32(OdUInt32 &incVal)
  { return interlockedIncrement32(incVal) - 1; }
  // Post-decrement
  inline OdUInt32 interlockedPostDecrement32(OdUInt32 &decVal)
  { return interlockedDecrement32(decVal) + 1; }

  // 16-bit atomic operations

  // Increments incVal and returns incremented result value.
  inline OdUInt16 interlockedIncrement16(OdUInt16 &incVal, OdUInt16 &refVal)
  {
#ifndef TD_SINGLE_THREAD
#ifdef InterlockedIncrement16
    ARGSUSED(refVal)
    return InterlockedIncrement16(reinterpret_cast<volatile SHORT*>(&incVal));
#else
    if (&incVal < &refVal)
    {
      volatile int *pReg = reinterpret_cast<volatile int*>(&incVal);
#ifdef ODA_BIGENDIAN
      return (OdUInt16)(::OdInterlockedExchangeAdd(pReg, 1 << 16) >> 16) + 1;
#else
      return (OdUInt16)::OdInterlockedIncrement(pReg);
#endif
    }
    else
    {
      volatile int *pReg = reinterpret_cast<volatile int*>(&refVal);
#ifdef ODA_BIGENDIAN
      return (OdUInt16)::OdInterlockedIncrement(pReg);
#else
      return (OdUInt16)(::OdInterlockedExchangeAdd(pReg, 1 << 16) >> 16) + 1;
#endif
    }
#endif
#else // TD_SINGLE_THREAD
    ARGSUSED(refVal)
    return ++incVal;
#endif // TD_SINGLE_THREAD
  }
  // Decrements decVal and returns decremented result value.
  inline OdUInt16 interlockedDecrement16(OdUInt16 &decVal, OdUInt16 &refVal)
  {
#ifndef TD_SINGLE_THREAD
#ifdef InterlockedDecrement16
    ARGSUSED(refVal)
    return InterlockedDecrement16(reinterpret_cast<volatile SHORT*>(&decVal));
#else
    if (&decVal < &refVal)
    {
      volatile int *pReg = reinterpret_cast<volatile int*>(&decVal);
#ifdef ODA_BIGENDIAN
      return (OdUInt16)(::OdInterlockedExchangeAdd(pReg, -(1 << 16)) >> 16) - 1;
#else
      return (OdUInt16)::OdInterlockedDecrement(pReg);
#endif
    }
    else
    {
      volatile int *pReg = reinterpret_cast<volatile int*>(&refVal);
#ifdef ODA_BIGENDIAN
      return (OdUInt16)::OdInterlockedDecrement(pReg);
#else
      return (OdUInt16)(::OdInterlockedExchangeAdd(pReg, -(1 << 16)) >> 16) - 1;
#endif
    }
#endif
#else // TD_SINGLE_THREAD
    ARGSUSED(refVal)
    return --decVal;
#endif // TD_SINGLE_THREAD
  }
#undef ARGSUSED
  // Post-increment
  inline OdUInt16 interlockedPostIncrement16(OdUInt16 &incVal, OdUInt16 &refVal)
  { return interlockedIncrement16(incVal, refVal) - 1; }
  // Post-decrement
  inline OdUInt16 interlockedPostDecrement16(OdUInt16 &decVal, OdUInt16 &refVal)
  { return interlockedDecrement16(decVal, refVal) + 1; }
} // namespace OdTrVisAtomics

/*
class tests
{
  struct A
  {
    OdUInt16 refCtr;
    OdUInt16 flags;
    A() { refCtr = 1; flags = 0xABCD; }
  };
  struct B
  {
    OdUInt16 flags;
    OdUInt16 refCtr;
    B() { refCtr = 1; flags = 0xABCD; }
  };
public:
  tests()
  {
    A a; B b;
    OdTrVisAtomics::interlockedIncrement16(a.refCtr, a.flags);
    OdTrVisAtomics::interlockedIncrement16(b.refCtr, b.flags);
    OdTrVisAtomics::interlockedDecrement16(a.refCtr, a.flags);
    OdTrVisAtomics::interlockedDecrement16(b.refCtr, b.flags);
  }
} _tests;
*/

#include "TD_PackPop.h"

#endif // ODTRVIS16BITATOMICOPS
