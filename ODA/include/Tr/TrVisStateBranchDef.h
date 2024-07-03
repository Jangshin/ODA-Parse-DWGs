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
// GLES2 device state branch definition

#ifndef ODTRVISSTATEBRANCHDEF
#define ODTRVISSTATEBRANCHDEF

#include "TD_PackPush.h"

#include "TrVisDefs.h"
#include "TrVisMetafileStream.h"

/** \details
    <group ExRender_Windows_Classes>
*/
struct OdTrVisStateBranchDef
{
  // List of GsMarker's
  OdTrVisGsMarkerArray m_markers;
  // List of child branches
  OdArray<OdTrVisStateBranchId, OdMemoryAllocator<OdTrVisStateBranchId> > m_childs;
};

/** \details
    <group ExRender_Windows_Classes>
*/
struct OdTrVisStateBranchMarkersRange
{
  OdTrVisGsMarker m_rangeFrom, m_rangeTo;
  OdTrVisStateBranchMarkersRange() : m_rangeFrom(kTrVisNullGsMarker), m_rangeTo(kTrVisNullGsMarker) { }
  OdTrVisStateBranchMarkersRange(OdTrVisGsMarker singleMarker) : m_rangeFrom(singleMarker), m_rangeTo(singleMarker) { }
  OdTrVisStateBranchMarkersRange(OdTrVisGsMarker markerFrom, OdTrVisGsMarker markerTo)
    : m_rangeFrom(markerFrom), m_rangeTo(markerTo) { }
  void set(OdTrVisGsMarker singleMarker = kTrVisNullGsMarker) { m_rangeFrom = m_rangeTo = singleMarker; }
  void set(OdTrVisGsMarker markerFrom, OdTrVisGsMarker markerTo) { m_rangeFrom = markerFrom; m_rangeTo = markerTo; }
  OdTrVisGsMarker markerFrom() const { return m_rangeFrom; }
  OdTrVisGsMarker markerTo() const { return m_rangeTo; }
  bool isSingleMarker() const { return (m_rangeFrom == m_rangeTo); }
  bool isFullRange() const { return isSingleMarker() && (m_rangeTo == m_rangeFrom); }
};

#include "TD_PackPop.h"

#endif // ODTRVISSTATEBRANCHDEF
