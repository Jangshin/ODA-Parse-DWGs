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

#if !defined(OD_RCSVISIBLEVOXELSITER_H__C8858A6D_D0D1_4DE6_B20E_260671F5523D__INCLUDED)
#define OD_RCSVISIBLEVOXELSITER_H__C8858A6D_D0D1_4DE6_B20E_260671F5523D__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"

#include "RootExport.h"
#include "SharedPtr.h"

#include "Ge/GePoint3dArray.h"
#include "CmEntityColorArray.h"

#include "Gi/GiPointCloud.h"

/** <group OdRcs_Classes>
  \details
  This is an interface class to iterate through the voxels visible in the
  current viewport.
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdRcsVisibleVoxelsIterator
{
public:

  /** \details
    Default destructor for objects of the OdRcsVisibleVoxelsIterator class.
  */
  virtual ~OdRcsVisibleVoxelsIterator() {}

  /** \details
    Moves the current iterator position to the visible voxel in the current
    viewport that will be iterated first.
  */
  virtual void start() = 0;

  /** \details
    Pteps the current iterator position to the next visible voxel in the current
    viewport.
  */
  virtual void step() = 0;

  /** details
    Indicates whether the traversal by this iterator object is complete.

    \returns
    True if the traversal by this iterator object is complete; false otherwise.
  */
  virtual bool done() const = 0;

  /** \details
    Fills a special structures used in rendering with pointers to point data from the current voxel pointed to by the iterator.

    \param componentsToProcess [in] Component flags used by GiPointCloud to obtain the required point attributes.

    \param pComponentsRaws [out] Pointer to a filled special structures stored in the voxel.
    \param rawsNumber [out] Number of special structures.
    \param flags [out] Size flags used to store each component of the point data.
    \param voxelIndex [out] Index of the voxel in scan database.
    \param numberOfPointsToDraw [out] Total number of visible points to be drawn.
    \param loadedPointsNumber [out] Number of points loaded.
  */
  virtual void getVoxelBuffer(OdUInt32 componentsToProcess,
    OdGiPointCloud::ComponentsRaw*& pComponentsRaws, OdUInt32& rawsNumber,
    OdUInt32& flags,
    OdUInt64& voxelIndex,
    OdUInt32& numberOfPointsToDraw, OdUInt32& loadedPointsNumber) = 0;

  /** \details
    Returns a number of loaded points to draw.

    \returns
    Corresponding value of type OdUInt32.
  */
  virtual OdUInt32 getNumberOfLoadedPointsToDraw() = 0;

  /** \details
    Returns a boolean value indicating whether any points in the current voxel are loaded.

    \returns
    Corresponding boolean value.
  */
  virtual bool hasPointsLoaded() = 0;
};

/** \details
  Shared pointer to objects of the OdRcsVisibleVoxelsIterator class.
*/
typedef OdSharedPtr<OdRcsVisibleVoxelsIterator> OdRcsVisibleVoxelsIteratorPtr;

#include "TD_PackPop.h"

#endif
