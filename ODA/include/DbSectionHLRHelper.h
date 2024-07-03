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

#ifndef _SECTIONHLRHELPER_EXPORT_DEFINED
#define _SECTIONHLRHELPER_EXPORT_DEFINED

#include "RxObject.h"
#include "DbObjectId.h"

class OdDbDatabase;

/** \details
This template class is a specialization of the OdSmartPtr class for OdDbSectionHLRHelper object pointers.
*/
class OdDbSectionHLRHelper;
typedef OdSmartPtr<OdDbSectionHLRHelper> OdDbSectionHLRHelperPtr;

/** \details
  This class implements kernel of helper to create flatterned and section geometry by
  hidden line remover and section modeller.

  <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbSectionHLRHelper : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbSectionHLRHelper);

  /** \details
   Returns database to initialize flattened and section geometry after creation.
  */
  virtual OdDbDatabase* database() const = 0;

  /** \details
   Set projection direction and section plane to create flattened and section geometry.

    \param ptBase [in]  Base point to define section plane.
    \param vrDir [in]  Normal vector of section plane and direction for flattened view and section creation.
    \param vrUp [in]  Up vector direction for flattened view and section creation.

    \remarks
    Returns eInvalidInput if direction vector is zero length or up vector is not perpendicular to 
    direction vector. Otherwise returns eOk.
  */
  virtual OdResult         setProjectionPlane(const OdGePoint3d& ptBase, const OdGeVector3d& vrDir, const OdGeVector3d& vrUp) = 0;

  /** \details
   Returns base point to define section plane.
  */
  virtual OdGePoint3d   projectionBase() const = 0;

  /** \details
   Returns normal vector of section plane and direction for flattened view and section creation.
  */
  virtual OdGeVector3d  projectionDirection() const = 0;

  /** \details
   Returns up vector direction for flattened view and section creation.
  */
  virtual OdGeVector3d  projectionUp() const = 0;

  /** \details
   Returns include tangental edges flag.
  */
  virtual bool          includeTangentalEdgesFlag() const = 0;

  /** \details
   Set include tangental edges flag.
  */
  virtual void          setIncludeTangentalEdgesFlag( bool bSet) = 0;

  /** \details
   Set tangential edges angle.

   \param dAngle [in]  The specified angle.
  */
  virtual void          setTangentalEdgesAngle(double dAngle) = 0;

  /** \details
   Set entities to create flattened and section geometry.

   \param arr3dObjects [in]  Array of object ids to be used in construction flattened view or section geometry.

   \remarks
   Returns eInvalidInput if no one entity from array is supported. Otherwise returns eOk.
   Method skip all non-supported entities.
  */
  virtual OdResult      setEntities(const OdDbObjectIdArray& arr3dObjects) = 0;

  /** \details
   Returns array of entity ids to create flattened views and section geometry.
  */
  virtual const OdArray<OdDbObjectId>& getEntities() const = 0;

  /** \details
   Returns 3d object extents of supported entity ids.
  */
  virtual OdGeExtents3d getExtents() const = 0;

  /** \details
   Calculate flattened views and section geometry.

   \param bCreateSection [in] Use section plane to cut 3d objects and create section hatches.
   \param bCreateHiddenLines [in] Create hidden line geometry.

    \remarks
   Returns eNotInitializedYet if no one entity was set to helper. Otherwise returns eOk.
  */
  virtual OdResult      createSectionHLR(bool bCreateSection, bool bCreateHiddenLines ) = 0;

  /** \details
   Returns non-dbro hatches of created by createSectionHLR method section.

   \param arrHatches [out] result entities.

    \remarks
   Returns false if section geometry was not created.
  */
  virtual bool          getSectionHatches( OdRxObjectPtrArray& arrHatches ) const = 0;

  /** \details
   Returns non-dbro hidden line geometry of created by createSectionHLR method flattened view geometry.

   \param arrHiddenLines [out] result entities.

    \remarks
   Returns false if flattened view geometry was not created.
  */
  virtual bool          getHiddenLines( OdRxObjectPtrArray& arrHiddenLines ) const = 0;

  /** \details
   Returns non-dbro visible line geometry of created by createSectionHLR method flattened view geometry.

   \param arrVisibleLines [out] result entities.

    \remarks
   Returns false if flattened view geometry was not created.
  */
  virtual bool          getVisibleLines( OdRxObjectPtrArray& arrVisibleLines ) const = 0;
  
  /** \details
  Returns is entity class is supported by section modeler and hidden line remover.

  \remarks
   At the moment supported OdDb3dSolid, OdDbSurtface, OdDbSubDMesh, OdDbRegion and OdDbBody classes.
  */
  static bool   isEntitySupported(const OdDbEntity* pEntity);

  /** \details
  Create instance of section and hidden line remover helper.

  \param pDb [in] database to initialize defaults for section and flattened view geometry.
  */
  static OdDbSectionHLRHelperPtr createObject(OdDbDatabase* pDb);

  /** \details
   Returns the default tangential angle.

   \returns default tangential angle.
  */
  static double getDefaultTangentAngle();
};

//====================================================================================================

#endif  /* _SECTIONHLRHELPER_EXPORT_DEFINED */
