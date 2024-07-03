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
#ifndef _OD_DB_GEOMAPFIELDS_PE_
#define _OD_DB_GEOMAPFIELDS_PE_

#include "DbGeoMap.h"
#include "DbGripPoints.h"
#include "TD_PackPush.h"

/** \details
  An abstract class that represents a protocol extension for the OdDbGeoMap class,
  which provides direct access to OdDbGeoMap class fields.

  <group OdDb_Classes>
*/
class DBGEOLOCATIONOBJ_EXPORT OdDbGeoMapFieldsPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbGeoMapFieldsPE);

  /** \details
    Default destructor.
  */
  virtual ~OdDbGeoMapFieldsPE() {};

  /** \details
    Returns the LOD of the map image.
    
    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual OdInt8 getLOD(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the IsOutOfDate flag of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual bool getIsOutOfDate(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the pixel data of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual const OdBinaryData & getPixelData(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the clip boundary array of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual const OdGePoint2dArray & getPtClipBnd(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the string array of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual const OdStringArray & getStrings(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the width vector of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual const OdGeVector3d & getvU(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the height vector of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual const OdGeVector3d & getvV(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the text height of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual double getTextHeight(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the text color of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual OdCmColor getTextColor(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the height of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual OdInt32 getHeight(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the width of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual OdInt32 getWidth(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the image width of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual double getImageWidth(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the image height of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual double getImageHeight(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the text position of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual const OdGePoint3d & getPtTextPosition(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the bottom left position of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual const OdGePoint3d & getPtImageBottomLeft(OdDbGeoMap * pGeoMap) const;

  /** \details
    Returns the resolution of the map image.

    \param pGeoMap [in] Pointer to the map image object.
  */
  virtual OdInt8 getResolution(OdDbGeoMap * pGeoMap) const;

  /** \details
    Sets the LOD (Level of Detail) for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param LOD [in] Level of detail.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setLOD(OdDbGeoMap * pGeoMap, OdInt8 LOD) const;

  /** \details
    Sets the IsOutOfDate flag for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param bIsOutOfDate [in] Boolean value for the IsOutOfDate flag.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setIsOutOfDate(OdDbGeoMap * pGeoMap, bool bIsOutOfDate) const;

  /** \details
    Sets the pixel data for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param pixelData [in] Image pixel data represented as binary data.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setPixelData(OdDbGeoMap * pGeoMap, const OdBinaryData & pixelData) const;

  /** \details
    Sets the clip boundary array for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param ptClipBnd [in] The clip boundary array for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setPtClipBnd(OdDbGeoMap * pGeoMap, const OdGePoint2dArray & ptClipBnd) const;

  /** \details
    Sets the string array for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param strings [in] The string array for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setStrings(OdDbGeoMap * pGeoMap, const OdStringArray & strings) const;

  /** \details
    Sets the width vector for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param vU [in] The width vector for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setvU(OdDbGeoMap * pGeoMap,const OdGeVector3d & vU) const;

  /** \details
    Sets the height vector for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param vV [in] The height vector for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setvV(OdDbGeoMap * pGeoMap, const OdGeVector3d & vV) const;

  /** \details
    Sets the text height for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param dTextHeight [in] The text height for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setTextHeight(OdDbGeoMap * pGeoMap, double dTextHeight) const;

  /** \details
    Sets the text color for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param cColor [in] The text color for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setTextColor(OdDbGeoMap * pGeoMap, const OdCmColor& cColor) const;

  /** \details
    Sets the height for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param height [in] The height for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setHeight(OdDbGeoMap * pGeoMap, OdInt32 height) const;

  /** \details
    Sets the width for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param width [in] The width for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setWidth(OdDbGeoMap * pGeoMap, OdInt32 width) const;

  /** \details
    Sets the image width for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param dImageWidth [in] The image width for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setImageWidth(OdDbGeoMap * pGeoMap, double dImageWidth) const;

  /** \details
    Sets the image height for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param dImageHeight [in] The image height for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setImageHeight(OdDbGeoMap * pGeoMap, double dImageHeight) const;

  /** \details
    Sets the text position for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param ptTextPosition [in] The text position for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setPtTextPosition(OdDbGeoMap * pGeoMap, const OdGePoint3d & ptTextPosition) const;

  /** \details
    Sets the bottom left position for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param ptImageBottomLeft [in] The bottom left position for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setPtImageBottomLeft(OdDbGeoMap * pGeoMap, const OdGePoint3d & ptImageBottomLeft) const;

  /** \details
    Sets the resolution for the map image.

    \param pGeoMap [in] Pointer to the map image object.
    \param Resolution [in] The resolution for the map image.

    \returns eOk if successful, or an appropriate error code otherwise.
  */
  virtual OdResult setResolution(OdDbGeoMap * pGeoMap, OdInt8 Resolution) const;
};

typedef OdSmartPtr<OdDbGeoMapFieldsPE> OdDbGeoMapFieldsPEPtr;


/** \details
  This class is the grip points protocol extension class for the OdDbGeoMap class.
  
  <group OdDb_Classes>
*/
class OdDbGeoMapGripPointsPE : public OdDbGripPointsPE
{
public:
  virtual OdResult getGripPoints(const OdDbEntity* pEntity, OdGePoint3dArray& gripPoints) const;
  virtual OdResult moveGripPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset);
  virtual OdResult getStretchPoints(const OdDbEntity* pEntity, OdGePoint3dArray& stretchPoints) const;
  virtual OdResult moveStretchPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset);
  virtual OdResult getOsnapPoints(const OdDbEntity* ent, OdDb::OsnapMode osnapMode, OdGsMarker gsSelectionMark,
    const OdGePoint3d& pickPoint, const OdGePoint3d& lastPoint, const OdGeMatrix3d& viewXform,
    OdGePoint3dArray& snapPoints) const;
};

#include "TD_PackPop.h"

#endif //_OD_DB_GEOMAPFIELDS_PE_
