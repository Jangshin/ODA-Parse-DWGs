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

#if !defined(OD_RCSPOINTDATAITERATOR_H__FD54AD4F_D4D4_48E8_9BD9_7E75B75E0C9F__INCLUDED)
#define OD_RCSPOINTDATAITERATOR_H__FD54AD4F_D4D4_48E8_9BD9_7E75B75E0C9F__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"

#include "RootExport.h"
#include "SharedPtr.h"

#include "Ge/GePoint3d.h"
#include "Ge/GePoint3dArray.h"
#include "CmEntityColorArray.h"
#include "Ge/GeVector3dArray.h"
#include "UInt16Array.h"
#include "UInt8Array.h"

/** <group OdRcs_Classes>
  \details
  This class is an interface class for the points data receiver that fills
  custom point cloud structure using points data from a voxel.

  \remarks
  Corresponding C++ library: RcsFileServices.
*/
class OdRcsPointDataReceiver
{
public:
  /** \details
    Destructor for objects of the OdRcsPointDataReceiver class.
  */
  virtual ~OdRcsPointDataReceiver() {}

  /** \details
    Set number of points that will be received.

    \param numberOfPoints [in]  Required number of points that are received.
  */
  virtual void setNumberOfPoints(OdUInt32 /*numberOfPoints*/) {}

  /** \details
    Set point's data.

    \param index       [in]  Index of the point.
    \param x           [in]  x coordinate of the point.
    \param y           [in]  y coordinate of the point.
    \param z           [in]  z coordinate of the point.
    \param r           [in]  Red color component of the point.
    \param g           [in]  Green color component of the point.
    \param b           [in]  Blue color component of the point.
    \param normalIndex [in]  Normal index of the point.
    \param intensity  [in]  Intencity of the point.
  */
  virtual void setPoint(OdUInt32 index, float x, float y, float z,
    OdUInt8 r, OdUInt8 g, OdUInt8 b, OdUInt16 normalIndex, OdUInt8 intensity) = 0;
};

/** <group OdRcs_Classes>
  \details
  This class is an interface class for the points data iterator that enables
  getting points from a voxel.

  \remarks
  Corresponding C++ library: RcsFileServices.
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdRcsPointDataIterator
{
public:

  /** \details
    Destructor for objects of the OdRcsPointDataIterator class.
  */
  virtual ~OdRcsPointDataIterator() {}

  /** \details
    Moves the current position to the beginning of the points data within the
    current voxel.
  */
  virtual void start() = 0;

  /** \details
    Returns true if and only if the traversal by this iterator object is
    complete.

    \returns
    The true value if the traversal by this iterator object is complete; false otherwise.
  */
  virtual bool done() const = 0;

  /** \details
    Fills the coordinates and color arrays. The iterator object steps forward.

    \param coordinates           [out]  Points coordinates array to be filled.
    \param colors                [out]  Points color array to be filled.
    \param requiredNumberOfPoints [in]  Required number of points to obtain.

    \returns
    Returns the actual number of points obtained.
  */
  virtual OdUInt32 getPoints(OdGePoint3dArray& coordinates, OdCmEntityColorArray& colors, 
    OdUInt32 requiredNumberOfPoints) = 0;

  /** \details
    Fills arrays of coordinates, colors and normals. The iterator object steps
    forward.

    \param coordinates           [out]  Points coordinates array to be filled.
    \param colors                [out]  Points color array to be filled.
    \param normals               [out]  Points normals array to be filled.
    \param requiredNumberOfPoints [in]  Required number of points to obtain.

    \returns
    Returns the actual number of points obtained.
  */
  virtual OdUInt32 getPoints(OdGePoint3dArray& coordinates, OdCmEntityColorArray& colors, 
    OdGeVector3dArray& normals,
    OdUInt32 requiredNumberOfPoints) = 0;

  /** \details
    Fills arrays of coordinates, colors, normal indexes and intensities. The
    iterator object steps forward.

    \param coordinates           [out]  Points coordinates array to be filled.
    \param colors                [out]  Points color array to be filled.
    \param normalIndexes         [out]  Points normal indexes array to be filled.
    \param intensities           [out]  Points intensities array to be filled.
    \param requiredNumberOfPoints [in]  Required number of points to obtain.

    \returns
    Returns the actual number of points obtained.
  */
  virtual OdUInt32 getPoints(OdGePoint3dArray& coordinates, OdCmEntityColorArray& colors, 
    OdUInt16Array& normalIndexes, OdUInt8Array& intensities,
    OdUInt32 requiredNumberOfPoints) = 0;

  /** \details
    Fills the point data using the given receiver object. The iterator object steps forward.

    \param receiver              [out]  Points coordinates array to be filled.
    \param requiredNumberOfPoints [in]  Required number of points to obtain.

    \returns
    Returns the actual number of points obtained.
  */
  virtual OdUInt32 getPoints(OdRcsPointDataReceiver& receiver,
    OdUInt32 requiredNumberOfPoints) = 0;
};

/** \details
  Shared pointer to objects of the OdRcsPointDataIterator class.
*/
typedef OdSharedPtr<OdRcsPointDataIterator> OdRcsPointDataIteratorPtr;

#include "TD_PackPop.h"

#endif
