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


#include "OdHeap.h"

// StaticRxObject.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(ODSTATICRXOBJECT_INCLUDED_)
#define ODSTATICRXOBJECT_INCLUDED_

/** \details
    <group OdRx_Classes>

    This template class provides the <link smart_pointers_definition_empty.html, empty implementation of counting references>  
    for instances of classes derived from the OdRxObject class.

    \sa
    TD_Db

    \remarks
    When you use this template class, the numRefs method is inherited from the OdRxObject class in the default definition.
    The numRefs method returns 1 by default.

    \sa
    <link smart_pointers_example_count_empty.html, Example of Counting References>

    \sa
    <link smart_pointers_overview.html, Overview of Smart Pointer Classes> 

    The OdRxObjectImpl class
*/
template<class T>
class OdStaticRxObject : public T
{
public:
#ifndef SWIG
#if (defined(_MSC_VER) && (_MSC_VER > 1800)) || (defined(__cplusplus) && (__cplusplus > 199711L))
  using T::T;
#endif
#endif
  /** \details
    Simulates the incrementing of the reference counter non-changing it.
  */
  void addRef() { }
  /** \details
    Simulates the decrementing of the reference counter non-changing it.
  */
  void release() ODRX_NOEXCEPT { }
};

/** \details
    <group OdRx_Classes>

    This is a variant of OdStaticRxObject for multiple inheritance
*/
template<class T1, class ... T>
class OdStaticRxObjectM : public T1, public T...
{
public:
  ODRX_USING_HEAP_OPERATORS(T1);

  /** \details
    Simulates the incrementing of the reference counter non-changing it.
  */
  void addRef() { }
  /** \details
    Simulates the decrementing of the reference counter non-changing it.
  */
  void release() ODRX_NOEXCEPT { }
};

#endif // !defined(ODSTATICRXOBJECT_INCLUDED_)

