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

#ifndef _ODGILOCALDRAWABLEDESC_INCLUDED_
#define _ODGILOCALDRAWABLEDESC_INCLUDED_

#include "TD_PackPush.h"

#include "Gi/GiPathNode.h"
#include "Gs/GsSelectionReactor.h"
#include "Ge/GeMatrix3d.h"

/** \details
    Local implementation for OdGiDrawableDesc and OdGiPathNode pure virtual classes.
    <group OdGi_Classes> 
*/
struct OdGiLocalDrawableDesc : OdGiDrawableDesc, OdGiPathNode
{
  OdGiDrawableDesc*& _pPlaceToRestore;
  OdGsMarker         _nSelectionMarker;
  OdGeMatrix3d       _xModelToWorld; // Model transform this drawable is being drawn with
  OdGeMatrix3d      *_pxModelToWorld;
  inline OdGiLocalDrawableDesc(OdGiDrawableDesc*& pParentDesc)
    : _pPlaceToRestore(pParentDesc)
    , _nSelectionMarker(0) /* kNullSubentIndex */
    , _pxModelToWorld(0) // NULL means identity
  {
    pParent = pParentDesc;
    _pPlaceToRestore = this;
  }
  inline ~OdGiLocalDrawableDesc()
  {
    _pPlaceToRestore = pParent;
  }

  // OdGsPathNode interface

  /** \details
    Retrieves a parent node.
    \returns
    pointer to the OdGiPathNode that represents a parent node.
  */
  const OdGiPathNode* parent() const
  {
    return static_cast<const OdGiLocalDrawableDesc*>(pParent);
  }

  /** \details
    Retrieves a persistent drawable identifier associated with this node.
    \returns
    pointer to the OdDbStub that represents a persistent drawable identifier.
  */
  OdDbStub* persistentDrawableId() const
  {
    return persistId;
  }

  /** \details
    Retrieves a transient drawable associated with this node.
    \returns
    pointer to the OdGiDrawable that represents a transient drawable.
  */
  const OdGiDrawable* transientDrawable() const
  {
    return pTransientDrawable;
  }

  /** \details
    Retrieves a selection marker.
    \returns
    graphics system selection marker.
  */
  OdGsMarker selectionMarker() const
  {
    return _nSelectionMarker;
  }

  /** \details
    Retrieves a model to world transform matrix.
    \returns
    pointer to the OdGeMatrix3d that a transform matrix.
  */
  const OdGeMatrix3d* modelToWorld() const {
    return _pxModelToWorld;
  }

  /** \details
    Sets a model to world transform matrix.
    \param x [in]  Transformation matrix.
  */
  void setModelToWorld(const OdGeMatrix3d& x) {
    _xModelToWorld = x;
    _pxModelToWorld = &_xModelToWorld;
  }
};

#include "TD_PackPop.h"

#endif // #ifndef _ODGILOCALDRAWABLEDESC_INCLUDED_
