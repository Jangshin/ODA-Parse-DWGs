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

#ifndef _ODDBGEOMAP_INCLUDED_
#define _ODDBGEOMAP_INCLUDED_

#include "DbRasterImage.h"
#include "Gi/GiRasterWrappers.h"
#include "OdGeoMapType.h"

#include "TD_PackPush.h"

/** \details
  This class represents an embedded raster image that is captured from a portion of a live map.

  <group OdDb_Classes>
*/
class DBGEOLOCATIONOBJ_EXPORT OdDbGeoMap : public OdDbRasterImage
{
public:
  ODDB_DECLARE_MEMBERS(OdDbGeoMap);

  /** \details
    Default constructor.
  */
  OdDbGeoMap();

  /** \details
    Default destructor.
  */
  virtual ~OdDbGeoMap();

  /** \details
    Returns the bottom left corner point of the image frame.
  */
  OdGePoint3d bottomLeftPt() const;

  /** \details
    Returns the height of the image frame.
  */
  double height() const;

  /** \details
    Returns the width of the image frame.
  */
  double width() const;

  /** \details
    Returns the bottom left corner of the embedded image.
  */
  OdGePoint3d imageBottomLeftPt() const;

  /** \details
    Returns the height of the embedded image.
  */
  double imageHeight() const;

  /** \details
    Returns the width of the embedded image.
  */
  double imageWidth() const;

  /** \details
    Returns the resolution of the map image that is applied on top of the LOD.
  */
  OdGeoMapResolution resolution() const;

  /** \details
    Sets the resolution for the map image that is applied on top of the LOD.

    \param resolution [in] Resolution enum value.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  OdResult setResolution(OdGeoMapResolution resolution);

  /** \details
    Returns the LOD (Level Of Detail, zoom level) of the map image. Updating the image resets this value.
  */
  OdInt8 LOD() const;

  /** \details
    Returns the current map type of the map image.
  */
  OdGeoMapType mapType() const;

  /** \details
    Sets the current map type for the map image.

    \param mapType [in] Map type enum value.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  OdResult setMapType(OdGeoMapType mapType);

  /** \details
    Returns a flag that indicates whether the image is up to date.
  */
  bool isOutOfDate() const;

  /** \details
    Updates the embedded image by recapturing an area from the live map.

    \param bReset [in] Indicates whether to capture the image in the optimal screen resolution.
    If true, the LOD and resolution are reset to optimal values.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  OdResult updateMapImage(bool bReset = false);

  OdResult dwgInFields(OdDbDwgFiler* pFiler) ODRX_OVERRIDE;
  void dwgOutFields(OdDbDwgFiler* pFiler) const ODRX_OVERRIDE;
  OdResult dxfInFields(OdDbDxfFiler* pFiler) ODRX_OVERRIDE;
  void dxfOutFields(OdDbDxfFiler* pFiler) const ODRX_OVERRIDE;

  OdDbObjectPtr decomposeForSave(OdDb::DwgVersion ver, OdDbObjectId& replaceId, bool& exchangeXData) ODRX_OVERRIDE;
  void composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;
  OdResult subErase(bool bErasing) ODRX_OVERRIDE;
  void subClose() ODRX_OVERRIDE;
  OdResult  subTransformBy(const OdGeMatrix3d& xform) ODRX_OVERRIDE;

  // OdDbRasterImage
  OdDbObjectId imageDefId() const ODRX_OVERRIDE;
  OdResult getVertices(OdGePoint3dArray& vertices) const ODRX_OVERRIDE;
  OdResult getImageVertices(OdGePoint3dArray& vertices) const;
  OdGeVector2d imageSize(bool bGetCachedValue = false) const ODRX_OVERRIDE;
  const OdGePoint2dArray& clipBoundary() const ODRX_OVERRIDE;

  OdResult  setBrightness(OdInt8 value) ODRX_OVERRIDE;
  OdInt8    brightness() const ODRX_OVERRIDE;

  OdResult  setContrast(OdInt8 value) ODRX_OVERRIDE;
  OdInt8    contrast() const ODRX_OVERRIDE;

  OdResult  setFade(OdInt8 value) ODRX_OVERRIDE;
  OdInt8    fade() const ODRX_OVERRIDE;

  virtual OdGiRasterImagePtr image(bool load = true) const;

  void getOrientation(OdGePoint3d& origin, OdGeVector3d& u, OdGeVector3d& v) const ODRX_OVERRIDE;
  bool setOrientation(const OdGePoint3d & ptOrigin, const OdGeVector3d & u, const OdGeVector3d & v) ODRX_OVERRIDE;

  void dragStatus(const OdDb::DragStat) ODRX_OVERRIDE;
protected:
  bool subWorldDraw(OdGiWorldDraw* pWorldDraw) const ODRX_OVERRIDE;
  void subViewportDraw(OdGiViewportDraw* pViewportDraw) const ODRX_OVERRIDE;
  
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const ODRX_OVERRIDE;

  void updateMapImageIfNeeded(bool bReset = false) const;

  friend class OdDbGeoMapFieldsPE;
};

typedef OdSmartPtr<OdDbGeoMap> OdDbGeoMapPtr;


/** \details
  This class represents geomap definition objects in the OdDbDatabase instance.
  
  \remarks
  Geomap definitions (OdDbGeoMapDef objects) work with geomap (OdDbGeoMap) entities
  in the same way that block table records (OdDbBlockTableRecord objects) work with block references
  (OdDbBlockReference entities).
  
  <group OdDb_Classes>
*/
class DBGEOLOCATIONOBJ_EXPORT OdDbGeoMapDef : public OdDbRasterImageDef
{
public:
  ODDB_DECLARE_MEMBERS(OdDbGeoMapDef);

  OdDbGeoMapDef();
  virtual ~OdDbGeoMapDef();

  /** \details
    Returns the OdDbGeoMap object associated with this OdDbGeoMapDef object.
  */
  virtual OdGiRasterImagePtr image(bool load = true);

  OdResult    dwgInFields(OdDbDwgFiler* pFiler);
  void        dwgOutFields(OdDbDwgFiler* pFiler) const;
};

typedef OdSmartPtr<OdDbGeoMapDef> OdDbGeoMapDefPtr;

#include "TD_PackPop.h"

#endif //_ODDBGEOMAP_INCLUDED_
