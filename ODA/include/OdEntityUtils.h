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




#ifndef   _OD_ENTITY_UTILS_H_
#define   _OD_ENTITY_UTILS_H_

#include "DbEntity.h"

/** \details
    Defines types object creaion.
  */
enum class BoundaryTypeEnum
{
  /** A OdDbRegion object. */
  eRegionBoundary = 0,
  /** A OdDbPolyline object. */
  ePolylineBoundary = 1
};

/** \details
     Creates OdDbRegions or a OdDbPolylines from enclosed areas. 

    \param pDb               [in] The database from which the entities will be obtained to build a boundary.
    \param pickPoint         [in] Point in the WCS.
    \param boundaryType      [in] Set 0 to create a region around a set of objects. Otherwise created closed polyline around a set of objects.
    \param bDetectIsland     [in] Set true if need create closed loops inner of loop created around pick point. False if create just one loop around pick point.
                                E.g. "if this parameter is set then inner islands will be created inside the outer boundary defined by the pick point".
    \param boundaryEntityOut [out] Created array of boundries
    \param plane             [in][optional] The plane on which the entity is located to form the boundary. If 0, then the plane will be taken as the UCS for the current viewport.
    \param selectionSet      [in][optional] Selections entity set to build boundary. If empty - will used entityes on current viewport extents.
    \param dGap              [in][optional] Specifies the size of possible gaps between entities when creating a boundary.
    
    \returns eOk                     if successful.
             eNoDatabase             if database not specified.
             eSubSelectionSetEmpty   if can't get set of entities from current view.
             eIllegalEntityType      if can't create a OdDbPolylines from entities.
             eGeneralModelingFailure if can't create a boundary from entities.
             eInvalidView            if can't access to active viewport.
  */
DBENT_EXPORT OdResult boundary(OdDbDatabase* pDb, const OdGePoint3d& pickPoint, const BoundaryTypeEnum boundaryType, const bool bDetectIsland,
  OdDbEntityPtrArray& boundaryEntityOut, const OdGePlane* plane = 0, const OdDbEntityPtrArray* selectionSet = 0, const double dGap = 0.);

#endif
