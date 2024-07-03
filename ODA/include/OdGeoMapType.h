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

#ifndef _ODGEOMAPTYPE_INCLUDED_
#define _ODGEOMAPTYPE_INCLUDED_

#include "OdaCommon.h"

#include "TD_PackPush.h"

/** \details
  Represents LiveMap and OdDbGeoMap map types.

  <group !!RECORDS_tdrawings_apiref>
*/
enum OdGeoMapType
{
  /** Live map is off. */
  kNoMap = 0,
  /** Bing Aerial representation of a live map. */
  kAerial = 1,
  /** Bing Aerial representation of a live map. */
  kBingAerial = kAerial,
  /** Bing Road representation of a live map. */
  kRoad = 2,
  /** Bing Road representation of a live map. */
  kBingRoad = kRoad,
  /** Bing Hybrid representation of a live map */
  kHybrid = 3,
  /** Bing Hybrid representation of a live map */
  kBingHybrid = kHybrid,
  /** Esri Imagery representation of a live map */
  kEsriImagery = 4,
  /** Esri Open Street Map representation of a live map */
  kEsriOpenStreetMap = 5,
  /** Esri Streets representation of a live map */
  kEsriStreets = 6,
  /** Esri Light Gray representation of a live map */
  kEsriLightGray = 7,
  /** Esri Dark Gray representation of a live map */
  kEsriDarkGray = 8
};


/** \details
  This enum value is applied on top of a live map LOD (Level Of Detail) value.

  <group !!RECORDS_tdrawings_apiref>
*/
enum OdGeoMapResolution
{
  /** One level less than the current LOD. */
  kCoarse = -1,
  /** No changes to the LOD are applied. */
  kOptimal = 0,
  /** One level higher than the current LOD. */
  kFine = 1,
  /** Two levels higher than the current LOD. */
  kFiner = 2
};

#include "TD_PackPop.h"

#endif //_ODGEOMAPTYPE_INCLUDED_
