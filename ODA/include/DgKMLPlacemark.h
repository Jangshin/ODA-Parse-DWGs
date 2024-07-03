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
#ifndef __DG_PLACEMARK_H__
#define __DG_PLACEMARK_H__

#include "DgApplicationData.h"
#include "DgElementIterator.h"
#include "DgGeoData.h"
#include "DgModel.h"
#include <map>

//--------------------------------------------------------------


//=============================================================================

class OdDgKMLPlacemarkSource;
typedef OdSmartPtr<OdDgKMLPlacemarkSource> OdDgKMLPlacemarkSourcePtr;

/** \details
An abstract class that represents a protocol extension for an OdDgKMLPlacemarkSource object.

<group OdDg_Classes>
*/
class TG_EXPORT OdDgKMLPlacemarkSource : public OdRxObject
{
public:
  enum OdDgKMLPlacemarkType
  {
    kUndefined = 0,
    kFile      = 1,
    kDatum     = 2,
    kGCS       = 3    
  };

public:
  ODRX_DECLARE_MEMBERS(OdDgKMLPlacemarkSource);

  virtual OdDgKMLPlacemarkSource::OdDgKMLPlacemarkType getType() const = 0;

  virtual OdString getName() const = 0;
  virtual void     setName(const OdString& strName) = 0;

  virtual double   getLongitude() const = 0;
  virtual void     setLongitude(double dLongitude) = 0;

  virtual double   getLatitude() const = 0;
  virtual void     setLatitude(double dLatitude) = 0;

  virtual double   getElevation() const = 0;
  virtual void     setElevation(double dElevation) = 0;

  static OdDgKMLPlacemarkSourcePtr createObject(OdDgKMLPlacemarkSource::OdDgKMLPlacemarkType uProjType);
};

//=============================================================================

/** \details
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgFileKMLPlacemark : public OdDgKMLPlacemarkSource
{
public:
  ODRX_DECLARE_MEMBERS(OdDgFileKMLPlacemark);

  virtual OdString getFilename() const = 0;
  virtual void     setFilename(const OdString& strFileName) = 0;
};

typedef OdSmartPtr<OdDgFileKMLPlacemark> OdDgFileKMLPlacemarkPtr;

//=============================================================================

/** \details
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGCSKMLPlacemark : public OdDgKMLPlacemarkSource
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGCSKMLPlacemark);

  virtual OdString getGCSName() const = 0;
  virtual void     setGCSName(const OdString& strName) = 0;

  virtual double   getInputEasting() const = 0;
  virtual void     setInputEasting(double dOffset) = 0;

  virtual double   getInputNorthing() const = 0;
  virtual void     setInputNorthing(double dOffset) = 0;

  virtual double   getInputElevation() const = 0;
  virtual void     setInputElevation(double dElevation) = 0;
};

typedef OdSmartPtr<OdDgGCSKMLPlacemark> OdDgGCSKMLPlacemarkPtr;

//=============================================================================

/** \details
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgDatumKMLPlacemark : public OdDgKMLPlacemarkSource
{
public:
  ODRX_DECLARE_MEMBERS(OdDgDatumKMLPlacemark);

  virtual OdString getDatumName() const = 0;
  virtual void     setDatumName(const OdString& strName) = 0;

  virtual double   getInputLongitude() const = 0;
  virtual void     setInputLongitude(double dLongitude) = 0;

  virtual double   getInputLatitude() const = 0;
  virtual void     setInputLatitude(double dLatitude) = 0;

  virtual double   getInputElevation() const = 0;
  virtual void     setInputElevation(double dElevation) = 0;
};

typedef OdSmartPtr<OdDgDatumKMLPlacemark> OdDgDatumKMLPlacemarkPtr;

//=============================================================================

class OdDgKMLPlacemark2d;
typedef OdSmartPtr<OdDgKMLPlacemark2d> OdDgKMLPlacemark2dPtr;

//=============================================================================

/** \details
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgKMLPlacemark2d : public OdDgGraphicsElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgKMLPlacemark2d);

  virtual OdString      getName() const;
  virtual void          setName(const OdString& name);

  virtual double        getLongitude() const;
  virtual void          setLongitude(double dLongitude);

  virtual double        getLatitude() const;
  virtual void          setLatitude(double dLatitude);

  virtual double        getElevation() const;
  virtual void          setElevation(double dElevation);

  virtual OdDgKMLPlacemarkSourcePtr getSource() const;
  virtual void          setSource(const OdDgKMLPlacemarkSourcePtr& pSource);

  virtual OdGePoint2d   getOrigin() const;
  virtual void          setOrigin(const OdGePoint2d& origin);

  virtual double        getRotation() const;
  virtual void          setRotation(double dAngle);

  virtual double        getScale() const;
  virtual void          setScale(double dScale);

  virtual void          setColorIndex(OdUInt32 index, bool doSubents = false);
  virtual void          setColor(ODCOLORREF color, bool doSubents = false);
  virtual void          setColor(const OdDgCmColor& color, bool doSubents = false);
  virtual void          setGraphicsGroupEntryId(OdUInt32 value, bool doSubents = false);
  virtual void          setClass(Class newClass, bool doSubents = false);
  virtual void          setLevelEntryId(OdUInt32 index, bool doSubents = false);
  virtual void          setLevelId(const OdDgElementId& levelId, bool doSubents = false);
  virtual void          setLineStyleEntryId(OdInt32 iLineStyle, bool doSubents = false);
  virtual void          setLineStyleId(const OdDgElementId& lineStyleId, bool doSubents = false);
  virtual void          setLineWeight(OdUInt32 uLineWeight, bool doSubents = false);
  virtual void          setInvisibleFlag(bool visibility, bool doSubents = false);
  virtual void          setPriority(OdInt32 iPriority);

  virtual bool          getActivePlacemarkFlag() const;
  virtual void          setActivePlacemarkFlag(bool bSet);

  // OdGiDrawable overridden
  bool                  subWorldDraw(OdGiWorldDraw* pWd) const;
  OdUInt32              subSetAttributes(OdGiDrawableTraits* pDrwTraits) const;
  OdResult              subGetGeomExtents(OdUInt32 uExtentFlags, OdGeExtents3d& extents) const;
  OdResult              subGetGeomExtents(const OdDgElementId& idView, OdUInt32 uExtentFlags, OdGeExtents3d& extents) const;
  virtual void          subSetDatabaseDefaults(OdDgDatabase* pDb);

  virtual void          subHighlight(bool bDoIt = true, const OdDgFullSubentPath* pSubId = 0, bool highlightAll = false) const;

  virtual OdRxObjectPtr clone() const;
  virtual OdResult      erase(bool eraseIt = true);

  virtual OdResult      subExplode(OdRxObjectPtrArray& entitySet) const;
  virtual void          setGeometryModified(bool bSet);

  static OdDgKMLPlacemark2dPtr createPlacemarkByCoord(double dLongitude, double dLatitude, double dElevation, const OdString& strPlacementName, 
    OdDgDatabase* pDb, const OdDgModel* pModel = NULL );
  static OdDgKMLPlacemark2dPtr createPlacemarkByDatum(const OdString& strDatumName, double dLongitude, double dLatitude, double dElevation, const OdString& strPlacementName, 
    OdDgDatabase* pDb, const OdDgModel* pModel = NULL);
  static OdDgKMLPlacemark2dPtr createPlacemarkByGCS(const OdString& strGCSName, double dEasting, double dNorthing, double dElevation, const OdString& strPlacementName, 
    OdDgDatabase* pDb, const OdDgModel* pModel = NULL);
  static OdArray<OdDgKMLPlacemark2dPtr> createPlacemarkByKMLFile(const OdString& strKMLFileName, OdDgDatabase* pDb, const OdDgModel* pModel = NULL);
};

//=============================================================================

class OdDgKMLPlacemark3d;
typedef OdSmartPtr<OdDgKMLPlacemark3d> OdDgKMLPlacemark3dPtr;

//=============================================================================

/** \details
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgKMLPlacemark3d : public OdDgGraphicsElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgKMLPlacemark3d);

  virtual OdString      getName() const;
  virtual void          setName(const OdString& name);

  virtual double        getLongitude() const;
  virtual void          setLongitude(double dLongitude);

  virtual double        getLatitude() const;
  virtual void          setLatitude(double dLatitude);

  virtual double        getElevation() const;
  virtual void          setElevation(double dElevation);

  virtual OdDgKMLPlacemarkSourcePtr getSource() const;
  virtual void          setSource(const OdDgKMLPlacemarkSourcePtr& pSource);

  virtual OdGePoint3d   getOrigin() const;
  virtual void          setOrigin(const OdGePoint3d& origin);

  virtual OdGeMatrix3d  getRotation() const;
  virtual void          setRotation(const OdGeMatrix3d& matRotation);

  virtual double        getScale() const;
  virtual void          setScale(double dScale);

  virtual void          setColorIndex(OdUInt32 index, bool doSubents = false);
  virtual void          setColor(ODCOLORREF color, bool doSubents = false);
  virtual void          setColor(const OdDgCmColor& color, bool doSubents = false);
  virtual void          setGraphicsGroupEntryId(OdUInt32 value, bool doSubents = false);
  virtual void          setClass(Class newClass, bool doSubents = false);
  virtual void          setLevelEntryId(OdUInt32 index, bool doSubents = false);
  virtual void          setLevelId(const OdDgElementId& levelId, bool doSubents = false);
  virtual void          setLineStyleEntryId(OdInt32 iLineStyle, bool doSubents = false);
  virtual void          setLineStyleId(const OdDgElementId& lineStyleId, bool doSubents = false);
  virtual void          setLineWeight(OdUInt32 uLineWeight, bool doSubents = false);
  virtual void          setInvisibleFlag(bool visibility, bool doSubents = false);
  virtual void          setPriority(OdInt32 iPriority);

  // OdGiDrawable overridden
  bool                  subWorldDraw(OdGiWorldDraw* pWd) const;
  OdUInt32              subSetAttributes(OdGiDrawableTraits* pDrwTraits) const;
  OdResult              subGetGeomExtents(OdUInt32 uExtentFlags, OdGeExtents3d& extents) const;
  OdResult              subGetGeomExtents(const OdDgElementId& idView, OdUInt32 uExtentFlags, OdGeExtents3d& extents) const;
  virtual void          subSetDatabaseDefaults(OdDgDatabase* pDb);

  virtual void          subHighlight(bool bDoIt = true, const OdDgFullSubentPath* pSubId = 0, bool highlightAll = false) const;

  virtual OdRxObjectPtr clone() const;
  virtual OdResult      erase(bool eraseIt = true);

  virtual OdResult      subExplode(OdRxObjectPtrArray& entitySet) const;
  virtual void          setGeometryModified(bool bSet);

  virtual bool          getActivePlacemarkFlag() const;
  virtual void          setActivePlacemarkFlag(bool bSet);

  static OdDgKMLPlacemark3dPtr createPlacemarkByCoord(double dLongitude, double dLatitude, double dElevation, const OdString& strPlacementName, 
    OdDgDatabase* pDb, const OdDgModel* pModel = NULL);
  static OdDgKMLPlacemark3dPtr createPlacemarkByDatum(const OdString& strDatumName, double dLongitude, double dLatitude, double dElevation, const OdString& strPlacementName, 
    OdDgDatabase* pDb, const OdDgModel* pModel = NULL);
  static OdDgKMLPlacemark3dPtr createPlacemarkByGCS(const OdString& strGCSName, double dEasting, double dNorthing, double dElevation, const OdString& strPlacementName, 
    OdDgDatabase* pDb, const OdDgModel* pModel = NULL);
  static OdArray<OdDgKMLPlacemark3dPtr> createPlacemarkByKMLFile(const OdString& strKMLFileName, OdDgDatabase* pDb, const OdDgModel* pModel = NULL);
};

//=============================================================================

#endif // __DG_PLACEMARK_H__
