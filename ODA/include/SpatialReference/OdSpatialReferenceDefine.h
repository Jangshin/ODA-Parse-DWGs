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
#ifndef _ODSPATIALREFERENCE_ODSPATIALREFERENCEDEFINE_INCLUDED_
#define _ODSPATIALREFERENCE_ODSPATIALREFERENCEDEFINE_INCLUDED_

#include "RxObjectImpl.h"

#define ODSPREF_RX_IMPL_DECLARE_MEMBERS(ClassName)            \
public:                                                       \
  friend class ClassName;                                     \
  static ClassName##Impl* getImpl(const ClassName* pObj);     \
  ClassName##Impl(ClassName * pOwner);                        \
  virtual ~ClassName##Impl();

#define ODSPREF_RX_IMPL_WITH_OWNER_DECLARE_MEMBERS(ClassName) \
  ODSPREF_RX_IMPL_DECLARE_MEMBERS(ClassName)                  \
  protected:                                                  \
    ClassName* m_pOwner;

#define ODSPREF_RX_DECLARE_MEMBERS(ClassName)                 \
  friend class ClassName##Impl;                               \
  ODRX_DECLARE_MEMBERS(ClassName);                            \
  protected:                                                  \
    ClassName();                                              \
    ClassName(ClassName##Impl * pImpl);                       \
  public:                                                     \
    virtual ~ClassName();

#define ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(ClassName)       \
protected:                                                    \
  ClassName##Impl* m_pImpl;                                   \
  ODSPREF_RX_DECLARE_MEMBERS(ClassName)

#define ODSPREF_DEFINE_GET_IMPL(ClassName)                          \
ClassName##Impl * ClassName##Impl::getImpl(const ClassName * pObj)  \
{                                                                   \
  return (ClassName##Impl *)pObj->m_pImpl;                          \
}

#define ODSPREF_RX_DEFINE_MEMBERS(ClassName,ParentClass)             \
  ODRX_CONS_DEFINE_MEMBERS(ClassName, ParentClass, RXIMPL_CONSTR);   \
  ODSPREF_DEFINE_GET_IMPL(ClassName)

#define ODSPREF_RX_NO_CONS_DEFINE_MEMBERS(ClassName,ParentClass)     \
  ODRX_NO_CONS_DEFINE_MEMBERS(ClassName, ParentClass);               \
  ODSPREF_DEFINE_GET_IMPL(ClassName)

#endif //_ODSPATIALREFERENCE_ODSPATIALREFERENCEDEFINE_INCLUDED_
